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
typedef  int /*<<< orphan*/  mbedtls_asn1_buf ;
typedef  int /*<<< orphan*/  mbedtls_arc4_context ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int MBEDTLS_ERR_PKCS12_FEATURE_UNAVAILABLE ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA1 ; 
 int mbedtls_arc4_crypt (int /*<<< orphan*/ *,size_t,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_arc4_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_arc4_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_arc4_setup (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  mbedtls_zeroize (unsigned char*,int) ; 
 int pkcs12_pbe_derive_key_iv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mbedtls_pkcs12_pbe_sha1_rc4_128( mbedtls_asn1_buf *pbe_params, int mode,
                             const unsigned char *pwd,  size_t pwdlen,
                             const unsigned char *data, size_t len,
                             unsigned char *output )
{
#if !defined(MBEDTLS_ARC4_C)
    ((void) pbe_params);
    ((void) mode);
    ((void) pwd);
    ((void) pwdlen);
    ((void) data);
    ((void) len);
    ((void) output);
    return( MBEDTLS_ERR_PKCS12_FEATURE_UNAVAILABLE );
#else
    int ret;
    unsigned char key[16];
    mbedtls_arc4_context ctx;
    ((void) mode);

    mbedtls_arc4_init( &ctx );

    if( ( ret = pkcs12_pbe_derive_key_iv( pbe_params, MBEDTLS_MD_SHA1,
                                          pwd, pwdlen,
                                          key, 16, NULL, 0 ) ) != 0 )
    {
        return( ret );
    }

    mbedtls_arc4_setup( &ctx, key, 16 );
    if( ( ret = mbedtls_arc4_crypt( &ctx, len, data, output ) ) != 0 )
        goto exit;

exit:
    mbedtls_zeroize( key, sizeof( key ) );
    mbedtls_arc4_free( &ctx );

    return( ret );
#endif /* MBEDTLS_ARC4_C */
}