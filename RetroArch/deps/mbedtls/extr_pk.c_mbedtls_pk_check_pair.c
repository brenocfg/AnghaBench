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
struct TYPE_5__ {int (* check_pair_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ type; } ;

/* Variables and functions */
 int MBEDTLS_ERR_PK_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_PK_TYPE_MISMATCH ; 
 scalar_t__ MBEDTLS_PK_RSA ; 
 scalar_t__ MBEDTLS_PK_RSA_ALT ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mbedtls_pk_check_pair( const mbedtls_pk_context *pub, const mbedtls_pk_context *prv )
{
    if( pub == NULL || pub->pk_info == NULL ||
        prv == NULL || prv->pk_info == NULL ||
        prv->pk_info->check_pair_func == NULL )
    {
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );
    }

    if( prv->pk_info->type == MBEDTLS_PK_RSA_ALT )
    {
        if( pub->pk_info->type != MBEDTLS_PK_RSA )
            return( MBEDTLS_ERR_PK_TYPE_MISMATCH );
    }
    else
    {
        if( pub->pk_info != prv->pk_info )
            return( MBEDTLS_ERR_PK_TYPE_MISMATCH );
    }

    return( prv->pk_info->check_pair_func( pub->pk_ctx, prv->pk_ctx ) );
}