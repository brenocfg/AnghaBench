#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* ctx_free_func ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  block_size; int /*<<< orphan*/ * (* ctx_alloc_func ) () ;} ;
typedef  TYPE_1__ mbedtls_md_info_t ;
struct TYPE_6__ {TYPE_1__ const* md_info; int /*<<< orphan*/ * md_ctx; int /*<<< orphan*/ * hmac_ctx; } ;
typedef  TYPE_2__ mbedtls_md_context_t ;

/* Variables and functions */
 int MBEDTLS_ERR_MD_ALLOC_FAILED ; 
 int MBEDTLS_ERR_MD_BAD_INPUT_DATA ; 
 int /*<<< orphan*/ * mbedtls_calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

int mbedtls_md_setup( mbedtls_md_context_t *ctx, const mbedtls_md_info_t *md_info, int hmac )
{
    if( md_info == NULL || ctx == NULL )
        return( MBEDTLS_ERR_MD_BAD_INPUT_DATA );

    if( ( ctx->md_ctx = md_info->ctx_alloc_func() ) == NULL )
        return( MBEDTLS_ERR_MD_ALLOC_FAILED );

    if( hmac != 0 )
    {
        ctx->hmac_ctx = mbedtls_calloc( 2, md_info->block_size );
        if( ctx->hmac_ctx == NULL )
        {
            md_info->ctx_free_func( ctx->md_ctx );
            return( MBEDTLS_ERR_MD_ALLOC_FAILED );
        }
    }

    ctx->md_info = md_info;

    return( 0 );
}