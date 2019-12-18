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
struct TYPE_5__ {int /*<<< orphan*/ * (* ctx_alloc_func ) () ;} ;
typedef  TYPE_1__ mbedtls_pk_info_t ;
struct TYPE_6__ {TYPE_1__ const* pk_info; int /*<<< orphan*/ * pk_ctx; } ;
typedef  TYPE_2__ mbedtls_pk_context ;

/* Variables and functions */
 int MBEDTLS_ERR_PK_ALLOC_FAILED ; 
 int MBEDTLS_ERR_PK_BAD_INPUT_DATA ; 
 int /*<<< orphan*/ * stub1 () ; 

int mbedtls_pk_setup( mbedtls_pk_context *ctx, const mbedtls_pk_info_t *info )
{
    if( ctx == NULL || info == NULL || ctx->pk_info != NULL )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    if( ( ctx->pk_ctx = info->ctx_alloc_func() ) == NULL )
        return( MBEDTLS_ERR_PK_ALLOC_FAILED );

    ctx->pk_info = info;

    return( 0 );
}