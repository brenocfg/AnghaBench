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
typedef  int /*<<< orphan*/  mbedtls_pk_debug_item ;
struct TYPE_5__ {int /*<<< orphan*/  pk_ctx; TYPE_1__* pk_info; } ;
typedef  TYPE_2__ mbedtls_pk_context ;
struct TYPE_4__ {int /*<<< orphan*/  (* debug_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int MBEDTLS_ERR_PK_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_PK_TYPE_MISMATCH ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mbedtls_pk_debug( const mbedtls_pk_context *ctx, mbedtls_pk_debug_item *items )
{
    if( ctx == NULL || ctx->pk_info == NULL )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    if( ctx->pk_info->debug_func == NULL )
        return( MBEDTLS_ERR_PK_TYPE_MISMATCH );

    ctx->pk_info->debug_func( ctx->pk_ctx, items );
    return( 0 );
}