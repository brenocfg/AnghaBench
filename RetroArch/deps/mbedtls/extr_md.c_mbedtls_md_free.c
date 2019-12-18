#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* hmac_ctx; TYPE_1__* md_info; int /*<<< orphan*/ * md_ctx; } ;
typedef  TYPE_2__ mbedtls_md_context_t ;
struct TYPE_6__ {int block_size; int /*<<< orphan*/  (* ctx_free_func ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void mbedtls_md_free( mbedtls_md_context_t *ctx )
{
    if( ctx == NULL || ctx->md_info == NULL )
        return;

    if( ctx->md_ctx != NULL )
        ctx->md_info->ctx_free_func( ctx->md_ctx );

    if( ctx->hmac_ctx != NULL )
    {
        mbedtls_zeroize( ctx->hmac_ctx, 2 * ctx->md_info->block_size );
        mbedtls_free( ctx->hmac_ctx );
    }

    mbedtls_zeroize( ctx, sizeof( mbedtls_md_context_t ) );
}