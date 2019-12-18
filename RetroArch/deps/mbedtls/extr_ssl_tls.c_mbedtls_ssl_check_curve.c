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
struct TYPE_5__ {TYPE_1__* conf; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
typedef  scalar_t__ mbedtls_ecp_group_id ;
struct TYPE_4__ {scalar_t__* curve_list; } ;

/* Variables and functions */
 scalar_t__ const MBEDTLS_ECP_DP_NONE ; 

int mbedtls_ssl_check_curve( const mbedtls_ssl_context *ssl, mbedtls_ecp_group_id grp_id )
{
    const mbedtls_ecp_group_id *gid;

    if( ssl->conf->curve_list == NULL )
        return( -1 );

    for( gid = ssl->conf->curve_list; *gid != MBEDTLS_ECP_DP_NONE; gid++ )
        if( *gid == grp_id )
            return( 0 );

    return( -1 );
}