#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ unprocessed_len; scalar_t__ operation; int (* get_padding ) (unsigned char*,size_t,size_t*) ;int /*<<< orphan*/  unprocessed_data; int /*<<< orphan*/  iv; int /*<<< orphan*/  cipher_ctx; TYPE_2__* cipher_info; int /*<<< orphan*/  (* add_padding ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;} ;
typedef  TYPE_3__ mbedtls_cipher_context_t ;
struct TYPE_8__ {scalar_t__ mode; TYPE_1__* base; } ;
struct TYPE_7__ {int (* cbc_func ) (int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ;} ;

/* Variables and functions */
 scalar_t__ MBEDTLS_DECRYPT ; 
 scalar_t__ MBEDTLS_ENCRYPT ; 
 int MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED ; 
 scalar_t__ MBEDTLS_MODE_CBC ; 
 scalar_t__ MBEDTLS_MODE_CFB ; 
 scalar_t__ MBEDTLS_MODE_CTR ; 
 scalar_t__ MBEDTLS_MODE_ECB ; 
 scalar_t__ MBEDTLS_MODE_GCM ; 
 scalar_t__ MBEDTLS_MODE_STREAM ; 
 size_t mbedtls_cipher_get_block_size (TYPE_3__*) ; 
 int /*<<< orphan*/  mbedtls_cipher_get_iv_size (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int stub2 (int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int stub3 (unsigned char*,size_t,size_t*) ; 

int mbedtls_cipher_finish( mbedtls_cipher_context_t *ctx,
                   unsigned char *output, size_t *olen )
{
    if( NULL == ctx || NULL == ctx->cipher_info || NULL == olen )
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );

    *olen = 0;

    if( MBEDTLS_MODE_CFB == ctx->cipher_info->mode ||
        MBEDTLS_MODE_CTR == ctx->cipher_info->mode ||
        MBEDTLS_MODE_GCM == ctx->cipher_info->mode ||
        MBEDTLS_MODE_STREAM == ctx->cipher_info->mode )
    {
        return( 0 );
    }

    if( MBEDTLS_MODE_ECB == ctx->cipher_info->mode )
    {
        if( ctx->unprocessed_len != 0 )
            return( MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED );

        return( 0 );
    }

#if defined(MBEDTLS_CIPHER_MODE_CBC)
    if( MBEDTLS_MODE_CBC == ctx->cipher_info->mode )
    {
        int ret = 0;

        if( MBEDTLS_ENCRYPT == ctx->operation )
        {
            /* check for 'no padding' mode */
            if( NULL == ctx->add_padding )
            {
                if( 0 != ctx->unprocessed_len )
                    return( MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED );

                return( 0 );
            }

            ctx->add_padding( ctx->unprocessed_data, mbedtls_cipher_get_iv_size( ctx ),
                    ctx->unprocessed_len );
        }
        else if( mbedtls_cipher_get_block_size( ctx ) != ctx->unprocessed_len )
        {
            /*
             * For decrypt operations, expect a full block,
             * or an empty block if no padding
             */
            if( NULL == ctx->add_padding && 0 == ctx->unprocessed_len )
                return( 0 );

            return( MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED );
        }

        /* cipher block */
        if( 0 != ( ret = ctx->cipher_info->base->cbc_func( ctx->cipher_ctx,
                ctx->operation, mbedtls_cipher_get_block_size( ctx ), ctx->iv,
                ctx->unprocessed_data, output ) ) )
        {
            return( ret );
        }

        /* Set output size for decryption */
        if( MBEDTLS_DECRYPT == ctx->operation )
            return ctx->get_padding( output, mbedtls_cipher_get_block_size( ctx ),
                                     olen );

        /* Set output size for encryption */
        *olen = mbedtls_cipher_get_block_size( ctx );
        return( 0 );
    }
#else
    ((void) output);
#endif /* MBEDTLS_CIPHER_MODE_CBC */

    return( MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE );
}