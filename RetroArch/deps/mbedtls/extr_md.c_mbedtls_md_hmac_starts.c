#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sum ;
struct TYPE_5__ {TYPE_1__* md_info; int /*<<< orphan*/  md_ctx; int /*<<< orphan*/ * hmac_ctx; } ;
typedef  TYPE_2__ mbedtls_md_context_t ;
struct TYPE_4__ {size_t block_size; size_t size; int /*<<< orphan*/  (* update_func ) (int /*<<< orphan*/ ,unsigned char*,size_t) ;int /*<<< orphan*/  (* starts_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* finish_func ) (int /*<<< orphan*/ ,unsigned char*) ;} ;

/* Variables and functions */
 int MBEDTLS_ERR_MD_BAD_INPUT_DATA ; 
 int MBEDTLS_MD_MAX_SIZE ; 
 int /*<<< orphan*/  mbedtls_zeroize (unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

int mbedtls_md_hmac_starts( mbedtls_md_context_t *ctx, const unsigned char *key, size_t keylen )
{
    unsigned char sum[MBEDTLS_MD_MAX_SIZE];
    unsigned char *ipad, *opad;
    size_t i;

    if( ctx == NULL || ctx->md_info == NULL || ctx->hmac_ctx == NULL )
        return( MBEDTLS_ERR_MD_BAD_INPUT_DATA );

    if( keylen > (size_t) ctx->md_info->block_size )
    {
        ctx->md_info->starts_func( ctx->md_ctx );
        ctx->md_info->update_func( ctx->md_ctx, key, keylen );
        ctx->md_info->finish_func( ctx->md_ctx, sum );

        keylen = ctx->md_info->size;
        key = sum;
    }

    ipad = (unsigned char *) ctx->hmac_ctx;
    opad = (unsigned char *) ctx->hmac_ctx + ctx->md_info->block_size;

    memset( ipad, 0x36, ctx->md_info->block_size );
    memset( opad, 0x5C, ctx->md_info->block_size );

    for( i = 0; i < keylen; i++ )
    {
        ipad[i] = (unsigned char)( ipad[i] ^ key[i] );
        opad[i] = (unsigned char)( opad[i] ^ key[i] );
    }

    mbedtls_zeroize( sum, sizeof( sum ) );

    ctx->md_info->starts_func( ctx->md_ctx );
    ctx->md_info->update_func( ctx->md_ctx, ipad, ctx->md_info->block_size );

    return( 0 );
}