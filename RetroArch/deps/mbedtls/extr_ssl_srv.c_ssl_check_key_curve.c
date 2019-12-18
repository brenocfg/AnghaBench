#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_pk_context ;
typedef  scalar_t__ mbedtls_ecp_group_id ;
struct TYPE_6__ {scalar_t__ grp_id; } ;
typedef  TYPE_2__ mbedtls_ecp_curve_info ;
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_7__ {TYPE_1__ grp; } ;

/* Variables and functions */
 TYPE_4__* mbedtls_pk_ec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_check_key_curve( mbedtls_pk_context *pk,
                                const mbedtls_ecp_curve_info **curves )
{
    const mbedtls_ecp_curve_info **crv = curves;
    mbedtls_ecp_group_id grp_id = mbedtls_pk_ec( *pk )->grp.id;

    while( *crv != NULL )
    {
        if( (*crv)->grp_id == grp_id )
            return( 0 );
        crv++;
    }

    return( -1 );
}