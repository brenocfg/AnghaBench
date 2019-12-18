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
struct TYPE_5__ {int /*<<< orphan*/  md_ctx; TYPE_1__* md_info; } ;
typedef  TYPE_2__ mbedtls_md_context_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* process_func ) (int /*<<< orphan*/ ,unsigned char const*) ;} ;

/* Variables and functions */
 int MBEDTLS_ERR_MD_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char const*) ; 

int mbedtls_md_process( mbedtls_md_context_t *ctx, const unsigned char *data )
{
    if( ctx == NULL || ctx->md_info == NULL )
        return( MBEDTLS_ERR_MD_BAD_INPUT_DATA );

    ctx->md_info->process_func( ctx->md_ctx, data );

    return( 0 );
}