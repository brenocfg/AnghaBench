#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_aes_context ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_AES_DECRYPT ; 
 int /*<<< orphan*/  mbedtls_aes_crypt_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_aes_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_aes_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_aes_setkey_dec (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  mbedtls_zeroize (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  pem_pbkdf1 (unsigned char*,unsigned int,unsigned char*,unsigned char const*,size_t) ; 

__attribute__((used)) static void pem_aes_decrypt( unsigned char aes_iv[16], unsigned int keylen,
                               unsigned char *buf, size_t buflen,
                               const unsigned char *pwd, size_t pwdlen )
{
    mbedtls_aes_context aes_ctx;
    unsigned char aes_key[32];

    mbedtls_aes_init( &aes_ctx );

    pem_pbkdf1( aes_key, keylen, aes_iv, pwd, pwdlen );

    mbedtls_aes_setkey_dec( &aes_ctx, aes_key, keylen * 8 );
    mbedtls_aes_crypt_cbc( &aes_ctx, MBEDTLS_AES_DECRYPT, buflen,
                     aes_iv, buf, buf );

    mbedtls_aes_free( &aes_ctx );
    mbedtls_zeroize( aes_key, keylen );
}