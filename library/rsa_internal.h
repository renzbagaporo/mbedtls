/**
 * \file rsa_internal.h
 *
 * \brief Internal-only RSA public-key cryptosystem API.
 *
 * This file declares RSA-related functions that are to be used
 * only from within the Mbed TLS library itself.
 *
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */
#ifndef MBEDTLS_RSA_INTERNAL_H
#define MBEDTLS_RSA_INTERNAL_H

#include "mbedtls/rsa.h"

/**
 * \brief           Parse a PKCS#1 (ASN.1) encoded private RSA key.
 *
 * \param rsa       The RSA context where parsed data will be stored.
 * \param key       The buffer that contains the key.
 * \param keylen    The length of the key buffer in bytes.
 *
 * \return          0 in success
 * \return          MBEDTLS_ERR_ASN1_xxx in case of ASN.1 parsing errors.
 * \return          MBEDTLS_ERR_RSA_BAD_INPUT_DATA in case of invalid version.
 */
int mbedtls_rsa_key_parse(mbedtls_rsa_context *rsa, const unsigned char *key, size_t keylen);

/**
 * \brief           Parse a PKCS#1 (ASN.1) encoded public RSA key.
 *
 * \param rsa       The RSA context where parsed data will be stored.
 * \param p         Beginning of the buffer containing the key to be parsed.
 *                  On successful return, the referenced pointer will be
 *                  updated in order to point to the end of the parsed data.
 * \param end       End of the buffer containing the key to be parsed.
 *
 * \return          0 on success.
 * \return          MBEDTLS_ERR_ASN1_xxx in case of ASN.1 parsing errors.
 * \return          MBEDTLS_ERR_RSA_BAD_INPUT_DATA in case of importing or
 *                  priv/pub validation errors.
 */
int mbedtls_rsa_pubkey_parse(mbedtls_rsa_context *rsa, unsigned char **p,
                             const unsigned char *end);

/**
 * \brief           Write a PKCS#1 (ASN.1) encoded private RSA key.
 *
 * \param rsa       The RSA context which contains the data to be written.
 * \param start     Beginning of the buffer that will be filled with the
 *                  private key.
 * \param p         End of the buffer that will be filled with the private key.
 *                  On successful return, the referenced pointer will be
 *                  updated in order to point to the beginning of written data.
 *
 * \return          On success, the number of bytes written to the output buffer
 *                  (i.e. a value > 0).
 * \return          MBEDTLS_ERR_RSA_BAD_INPUT_DATA is the RSA context does not
 *                  cointain valid.
 * \return          MBEDTLS_ERR_ASN1_xxx in case of failure while writing to the
 *                  output buffer.
 *
 * \note            The output buffer is filled backward, i.e. starting from its
 *                  end and moving toward its start.
 */
int mbedtls_rsa_key_write(const mbedtls_rsa_context *rsa, unsigned char *start,
                          unsigned char **p);

/**
 * \brief           Parse a PKCS#1 (ASN.1) encoded public RSA key.
 *
 * \param rsa       The RSA context which contains the data to be written.
 * \param start     Beginning of the buffer that will be filled with the
 *                  private key.
 * \param p         End of the buffer that will be filled with the private key.
 *                  On successful return, the referenced pointer will be
 *                  updated in order to point to the beginning of written data.
 *
 * \return          On success, the number of bytes written to the output buffer
 *                  (i.e. a value > 0).
 * \return          MBEDTLS_ERR_RSA_BAD_INPUT_DATA is the RSA context does not
 *                  cointain valid.
 * \return          MBEDTLS_ERR_ASN1_xxx in case of failure while writing to the
 *                  output buffer.
 *
 * \note            The output buffer is filled backward, i.e. starting from its
 *                  end and moving toward its start.
 */
int mbedtls_rsa_pubkey_write(const mbedtls_rsa_context *rsa, unsigned char *start,
                             unsigned char **p);

#if defined(MBEDTLS_PKCS1_V21)
/**
 * \brief This function is analogue to \c mbedtls_rsa_rsassa_pss_sign().
 *        The only difference between them is that this function is more flexible
 *        on the parameters of \p ctx that are set with \c mbedtls_rsa_set_padding().
 *
 * \note  Compared to its counterpart, this function:
 *        - does not check the padding setting of \p ctx.
 *        - allows the hash_id of \p ctx to be MBEDTLS_MD_NONE,
 *          in which case it uses \p md_alg as the hash_id.
 *
 * \note  Refer to \c mbedtls_rsa_rsassa_pss_sign() for a description
 *        of the functioning and parameters of this function.
 */
int mbedtls_rsa_rsassa_pss_sign_no_mode_check(mbedtls_rsa_context *ctx,
                                              int (*f_rng)(void *, unsigned char *, size_t),
                                              void *p_rng,
                                              mbedtls_md_type_t md_alg,
                                              unsigned int hashlen,
                                              const unsigned char *hash,
                                              unsigned char *sig);
#endif /* MBEDTLS_PKCS1_V21 */

#endif /* rsa_internal.h */
