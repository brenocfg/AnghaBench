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
typedef  int /*<<< orphan*/  mbedtls_md_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  V; int /*<<< orphan*/  md_ctx; } ;
typedef  TYPE_1__ mbedtls_hmac_drbg_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_hmac_drbg_update (TYPE_1__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_md_get_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_md_hmac_starts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_md_setup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int mbedtls_hmac_drbg_seed_buf( mbedtls_hmac_drbg_context *ctx,
                        const mbedtls_md_info_t * md_info,
                        const unsigned char *data, size_t data_len )
{
    int ret;

    if( ( ret = mbedtls_md_setup( &ctx->md_ctx, md_info, 1 ) ) != 0 )
        return( ret );

    /*
     * Set initial working state.
     * Use the V memory location, which is currently all 0, to initialize the
     * MD context with an all-zero key. Then set V to its initial value.
     */
    mbedtls_md_hmac_starts( &ctx->md_ctx, ctx->V, mbedtls_md_get_size( md_info ) );
    memset( ctx->V, 0x01, mbedtls_md_get_size( md_info ) );

    mbedtls_hmac_drbg_update( ctx, data, data_len );

    return( 0 );
}