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
struct TYPE_6__ {int /*<<< orphan*/  pk_ctx; TYPE_1__* pk_info; } ;
typedef  TYPE_2__ mbedtls_pk_context ;
struct TYPE_5__ {int /*<<< orphan*/  (* ctx_free_func ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void mbedtls_pk_free( mbedtls_pk_context *ctx )
{
    if( ctx == NULL || ctx->pk_info == NULL )
        return;

    ctx->pk_info->ctx_free_func( ctx->pk_ctx );

    mbedtls_zeroize( ctx, sizeof( mbedtls_pk_context ) );
}