#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hmac_ctx; } ;
typedef  TYPE_1__ mbedtls_ssl_cookie_ctx ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  COOKIE_MD ; 
 int COOKIE_MD_OUTLEN ; 
 int /*<<< orphan*/  mbedtls_md_hmac_starts (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  mbedtls_md_info_from_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_md_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mbedtls_zeroize (unsigned char*,int) ; 

int mbedtls_ssl_cookie_setup( mbedtls_ssl_cookie_ctx *ctx,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng )
{
    int ret;
    unsigned char key[COOKIE_MD_OUTLEN];

    if( ( ret = f_rng( p_rng, key, sizeof( key ) ) ) != 0 )
        return( ret );

    ret = mbedtls_md_setup( &ctx->hmac_ctx, mbedtls_md_info_from_type( COOKIE_MD ), 1 );
    if( ret != 0 )
        return( ret );

    ret = mbedtls_md_hmac_starts( &ctx->hmac_ctx, key, sizeof( key ) );
    if( ret != 0 )
        return( ret );

    mbedtls_zeroize( key, sizeof( key ) );

    return( 0 );
}