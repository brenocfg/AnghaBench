#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  md_info; } ;
struct TYPE_7__ {scalar_t__ prediction_resistance; scalar_t__ reseed_counter; scalar_t__ reseed_interval; int /*<<< orphan*/  V; TYPE_2__ md_ctx; int /*<<< orphan*/ * f_entropy; } ;
typedef  TYPE_1__ mbedtls_hmac_drbg_context ;

/* Variables and functions */
 int MBEDTLS_ERR_HMAC_DRBG_INPUT_TOO_BIG ; 
 int MBEDTLS_ERR_HMAC_DRBG_REQUEST_TOO_BIG ; 
 size_t MBEDTLS_HMAC_DRBG_MAX_INPUT ; 
 size_t MBEDTLS_HMAC_DRBG_MAX_REQUEST ; 
 scalar_t__ MBEDTLS_HMAC_DRBG_PR_ON ; 
 int mbedtls_hmac_drbg_reseed (TYPE_1__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_hmac_drbg_update (TYPE_1__*,unsigned char const*,size_t) ; 
 size_t mbedtls_md_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_md_hmac_finish (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_md_hmac_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_md_hmac_update (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

int mbedtls_hmac_drbg_random_with_add( void *p_rng,
                               unsigned char *output, size_t out_len,
                               const unsigned char *additional, size_t add_len )
{
    int ret;
    mbedtls_hmac_drbg_context *ctx = (mbedtls_hmac_drbg_context *) p_rng;
    size_t md_len = mbedtls_md_get_size( ctx->md_ctx.md_info );
    size_t left = out_len;
    unsigned char *out = output;

    /* II. Check request length */
    if( out_len > MBEDTLS_HMAC_DRBG_MAX_REQUEST )
        return( MBEDTLS_ERR_HMAC_DRBG_REQUEST_TOO_BIG );

    /* III. Check input length */
    if( add_len > MBEDTLS_HMAC_DRBG_MAX_INPUT )
        return( MBEDTLS_ERR_HMAC_DRBG_INPUT_TOO_BIG );

    /* 1. (aka VII and IX) Check reseed counter and PR */
    if( ctx->f_entropy != NULL && /* For no-reseeding instances */
        ( ctx->prediction_resistance == MBEDTLS_HMAC_DRBG_PR_ON ||
          ctx->reseed_counter > ctx->reseed_interval ) )
    {
        if( ( ret = mbedtls_hmac_drbg_reseed( ctx, additional, add_len ) ) != 0 )
            return( ret );

        add_len = 0; /* VII.4 */
    }

    /* 2. Use additional data if any */
    if( additional != NULL && add_len != 0 )
        mbedtls_hmac_drbg_update( ctx, additional, add_len );

    /* 3, 4, 5. Generate bytes */
    while( left != 0 )
    {
        size_t use_len = left > md_len ? md_len : left;

        mbedtls_md_hmac_reset( &ctx->md_ctx );
        mbedtls_md_hmac_update( &ctx->md_ctx, ctx->V, md_len );
        mbedtls_md_hmac_finish( &ctx->md_ctx, ctx->V );

        memcpy( out, ctx->V, use_len );
        out += use_len;
        left -= use_len;
    }

    /* 6. Update */
    mbedtls_hmac_drbg_update( ctx, additional, add_len );

    /* 7. Update reseed counter */
    ctx->reseed_counter++;

    /* 8. Done */
    return( 0 );
}