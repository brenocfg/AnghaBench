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
struct TYPE_5__ {int /*<<< orphan*/  pk_ctx; TYPE_1__* pk_info; } ;
typedef  TYPE_2__ mbedtls_pk_context ;
struct TYPE_4__ {size_t (* get_bitlen ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t stub1 (int /*<<< orphan*/ ) ; 

size_t mbedtls_pk_get_bitlen( const mbedtls_pk_context *ctx )
{
    if( ctx == NULL || ctx->pk_info == NULL )
        return( 0 );

    return( ctx->pk_info->get_bitlen( ctx->pk_ctx ) );
}