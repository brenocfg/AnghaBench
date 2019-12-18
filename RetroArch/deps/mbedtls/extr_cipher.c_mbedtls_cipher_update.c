#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_gcm_context ;
struct TYPE_8__ {scalar_t__ operation; size_t unprocessed_len; unsigned char const* unprocessed_data; scalar_t__ cipher_ctx; TYPE_2__* cipher_info; int /*<<< orphan*/  iv; } ;
typedef  TYPE_3__ mbedtls_cipher_context_t ;
struct TYPE_7__ {scalar_t__ mode; TYPE_1__* base; } ;
struct TYPE_6__ {int (* ecb_func ) (scalar_t__,scalar_t__,unsigned char const*,unsigned char*) ;int (* cbc_func ) (scalar_t__,scalar_t__,size_t,int /*<<< orphan*/ ,unsigned char const*,unsigned char*) ;int (* cfb_func ) (scalar_t__,scalar_t__,size_t,size_t*,int /*<<< orphan*/ ,unsigned char const*,unsigned char*) ;int (* ctr_func ) (scalar_t__,size_t,size_t*,int /*<<< orphan*/ ,unsigned char const*,unsigned char const*,unsigned char*) ;int (* stream_func ) (scalar_t__,size_t,unsigned char const*,unsigned char*) ;} ;

/* Variables and functions */
 scalar_t__ MBEDTLS_DECRYPT ; 
 scalar_t__ MBEDTLS_ENCRYPT ; 
 int MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED ; 
 int MBEDTLS_ERR_CIPHER_INVALID_CONTEXT ; 
 scalar_t__ MBEDTLS_MODE_CBC ; 
 scalar_t__ MBEDTLS_MODE_CFB ; 
 scalar_t__ MBEDTLS_MODE_CTR ; 
 scalar_t__ MBEDTLS_MODE_ECB ; 
 scalar_t__ MBEDTLS_MODE_GCM ; 
 scalar_t__ MBEDTLS_MODE_STREAM ; 
 size_t mbedtls_cipher_get_block_size (TYPE_3__*) ; 
 int mbedtls_gcm_update (int /*<<< orphan*/ *,size_t,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,size_t) ; 
 int stub1 (scalar_t__,scalar_t__,unsigned char const*,unsigned char*) ; 
 int stub2 (scalar_t__,scalar_t__,size_t,int /*<<< orphan*/ ,unsigned char const*,unsigned char*) ; 
 int stub3 (scalar_t__,scalar_t__,size_t,int /*<<< orphan*/ ,unsigned char const*,unsigned char*) ; 
 int stub4 (scalar_t__,scalar_t__,size_t,size_t*,int /*<<< orphan*/ ,unsigned char const*,unsigned char*) ; 
 int stub5 (scalar_t__,size_t,size_t*,int /*<<< orphan*/ ,unsigned char const*,unsigned char const*,unsigned char*) ; 
 int stub6 (scalar_t__,size_t,unsigned char const*,unsigned char*) ; 

int mbedtls_cipher_update( mbedtls_cipher_context_t *ctx, const unsigned char *input,
                   size_t ilen, unsigned char *output, size_t *olen )
{
    int ret;
    size_t block_size = 0;

    if( NULL == ctx || NULL == ctx->cipher_info || NULL == olen )
    {
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );
    }

    *olen = 0;
    block_size = mbedtls_cipher_get_block_size( ctx );

    if( ctx->cipher_info->mode == MBEDTLS_MODE_ECB )
    {
        if( ilen != block_size )
            return( MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED );

        *olen = ilen;

        if( 0 != ( ret = ctx->cipher_info->base->ecb_func( ctx->cipher_ctx,
                    ctx->operation, input, output ) ) )
        {
            return( ret );
        }

        return( 0 );
    }

#if defined(MBEDTLS_GCM_C)
    if( ctx->cipher_info->mode == MBEDTLS_MODE_GCM )
    {
        *olen = ilen;
        return mbedtls_gcm_update( (mbedtls_gcm_context *) ctx->cipher_ctx, ilen, input,
                           output );
    }
#endif

    if ( 0 == block_size )
    {
        return MBEDTLS_ERR_CIPHER_INVALID_CONTEXT;
    }

    if( input == output &&
       ( ctx->unprocessed_len != 0 || ilen % block_size ) )
    {
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );
    }

#if defined(MBEDTLS_CIPHER_MODE_CBC)
    if( ctx->cipher_info->mode == MBEDTLS_MODE_CBC )
    {
        size_t copy_len = 0;

        /*
         * If there is not enough data for a full block, cache it.
         */
        if( ( ctx->operation == MBEDTLS_DECRYPT &&
                ilen <= block_size - ctx->unprocessed_len ) ||
             ( ctx->operation == MBEDTLS_ENCRYPT &&
                ilen < block_size - ctx->unprocessed_len ) )
        {
            memcpy( &( ctx->unprocessed_data[ctx->unprocessed_len] ), input,
                    ilen );

            ctx->unprocessed_len += ilen;
            return( 0 );
        }

        /*
         * Process cached data first
         */
        if( 0 != ctx->unprocessed_len )
        {
            copy_len = block_size - ctx->unprocessed_len;

            memcpy( &( ctx->unprocessed_data[ctx->unprocessed_len] ), input,
                    copy_len );

            if( 0 != ( ret = ctx->cipher_info->base->cbc_func( ctx->cipher_ctx,
                    ctx->operation, block_size, ctx->iv,
                    ctx->unprocessed_data, output ) ) )
            {
                return( ret );
            }

            *olen += block_size;
            output += block_size;
            ctx->unprocessed_len = 0;

            input += copy_len;
            ilen -= copy_len;
        }

        /*
         * Cache final, incomplete block
         */
        if( 0 != ilen )
        {
            if( 0 == block_size )
            {
                return MBEDTLS_ERR_CIPHER_INVALID_CONTEXT;
            }

            copy_len = ilen % block_size;
            if( copy_len == 0 && ctx->operation == MBEDTLS_DECRYPT )
                copy_len = block_size;

            memcpy( ctx->unprocessed_data, &( input[ilen - copy_len] ),
                    copy_len );

            ctx->unprocessed_len += copy_len;
            ilen -= copy_len;
        }

        /*
         * Process remaining full blocks
         */
        if( ilen )
        {
            if( 0 != ( ret = ctx->cipher_info->base->cbc_func( ctx->cipher_ctx,
                    ctx->operation, ilen, ctx->iv, input, output ) ) )
            {
                return( ret );
            }

            *olen += ilen;
        }

        return( 0 );
    }
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#if defined(MBEDTLS_CIPHER_MODE_CFB)
    if( ctx->cipher_info->mode == MBEDTLS_MODE_CFB )
    {
        if( 0 != ( ret = ctx->cipher_info->base->cfb_func( ctx->cipher_ctx,
                ctx->operation, ilen, &ctx->unprocessed_len, ctx->iv,
                input, output ) ) )
        {
            return( ret );
        }

        *olen = ilen;

        return( 0 );
    }
#endif /* MBEDTLS_CIPHER_MODE_CFB */

#if defined(MBEDTLS_CIPHER_MODE_CTR)
    if( ctx->cipher_info->mode == MBEDTLS_MODE_CTR )
    {
        if( 0 != ( ret = ctx->cipher_info->base->ctr_func( ctx->cipher_ctx,
                ilen, &ctx->unprocessed_len, ctx->iv,
                ctx->unprocessed_data, input, output ) ) )
        {
            return( ret );
        }

        *olen = ilen;

        return( 0 );
    }
#endif /* MBEDTLS_CIPHER_MODE_CTR */

#if defined(MBEDTLS_CIPHER_MODE_STREAM)
    if( ctx->cipher_info->mode == MBEDTLS_MODE_STREAM )
    {
        if( 0 != ( ret = ctx->cipher_info->base->stream_func( ctx->cipher_ctx,
                                                    ilen, input, output ) ) )
        {
            return( ret );
        }

        *olen = ilen;

        return( 0 );
    }
#endif /* MBEDTLS_CIPHER_MODE_STREAM */

    return( MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE );
}