#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_operation_t ;
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;
typedef  int /*<<< orphan*/  mbedtls_cipher_type_t ;
struct TYPE_4__ {int key_bitlen; int /*<<< orphan*/  iv_size; } ;
typedef  TYPE_1__ mbedtls_cipher_info_t ;
typedef  int /*<<< orphan*/  mbedtls_cipher_context_t ;
typedef  int /*<<< orphan*/  mbedtls_asn1_buf ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  iv ;

/* Variables and functions */
 int MBEDTLS_ERR_PKCS12_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_PKCS12_PASSWORD_MISMATCH ; 
 int mbedtls_cipher_finish (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  mbedtls_cipher_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* mbedtls_cipher_info_from_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_cipher_init (int /*<<< orphan*/ *) ; 
 int mbedtls_cipher_reset (int /*<<< orphan*/ *) ; 
 int mbedtls_cipher_set_iv (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int mbedtls_cipher_setkey (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int mbedtls_cipher_setup (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int mbedtls_cipher_update (int /*<<< orphan*/ *,unsigned char const*,size_t,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  mbedtls_zeroize (unsigned char*,int) ; 
 int pkcs12_pbe_derive_key_iv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*,int,unsigned char*,int /*<<< orphan*/ ) ; 

int mbedtls_pkcs12_pbe( mbedtls_asn1_buf *pbe_params, int mode,
                mbedtls_cipher_type_t cipher_type, mbedtls_md_type_t md_type,
                const unsigned char *pwd,  size_t pwdlen,
                const unsigned char *data, size_t len,
                unsigned char *output )
{
    int ret, keylen = 0;
    unsigned char key[32];
    unsigned char iv[16];
    const mbedtls_cipher_info_t *cipher_info;
    mbedtls_cipher_context_t cipher_ctx;
    size_t olen = 0;

    cipher_info = mbedtls_cipher_info_from_type( cipher_type );
    if( cipher_info == NULL )
        return( MBEDTLS_ERR_PKCS12_FEATURE_UNAVAILABLE );

    keylen = cipher_info->key_bitlen / 8;

    if( ( ret = pkcs12_pbe_derive_key_iv( pbe_params, md_type, pwd, pwdlen,
                                          key, keylen,
                                          iv, cipher_info->iv_size ) ) != 0 )
    {
        return( ret );
    }

    mbedtls_cipher_init( &cipher_ctx );

    if( ( ret = mbedtls_cipher_setup( &cipher_ctx, cipher_info ) ) != 0 )
        goto exit;

    if( ( ret = mbedtls_cipher_setkey( &cipher_ctx, key, 8 * keylen, (mbedtls_operation_t) mode ) ) != 0 )
        goto exit;

    if( ( ret = mbedtls_cipher_set_iv( &cipher_ctx, iv, cipher_info->iv_size ) ) != 0 )
        goto exit;

    if( ( ret = mbedtls_cipher_reset( &cipher_ctx ) ) != 0 )
        goto exit;

    if( ( ret = mbedtls_cipher_update( &cipher_ctx, data, len,
                                output, &olen ) ) != 0 )
    {
        goto exit;
    }

    if( ( ret = mbedtls_cipher_finish( &cipher_ctx, output + olen, &olen ) ) != 0 )
        ret = MBEDTLS_ERR_PKCS12_PASSWORD_MISMATCH;

exit:
    mbedtls_zeroize( key, sizeof( key ) );
    mbedtls_zeroize( iv,  sizeof( iv  ) );
    mbedtls_cipher_free( &cipher_ctx );

    return( ret );
}