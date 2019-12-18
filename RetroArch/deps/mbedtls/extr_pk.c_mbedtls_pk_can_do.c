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
typedef  int /*<<< orphan*/  mbedtls_pk_type_t ;
struct TYPE_5__ {TYPE_1__* pk_info; } ;
typedef  TYPE_2__ mbedtls_pk_context ;
struct TYPE_4__ {int (* can_do ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

int mbedtls_pk_can_do( const mbedtls_pk_context *ctx, mbedtls_pk_type_t type )
{
    /* null or NONE context can't do anything */
    if( ctx == NULL || ctx->pk_info == NULL )
        return( 0 );

    return( ctx->pk_info->can_do( type ) );
}