#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
typedef  int /*<<< orphan*/  mbedtls_ecp_group ;

/* Variables and functions */
 scalar_t__ ECP_TYPE_MONTGOMERY ; 
 scalar_t__ ECP_TYPE_SHORT_WEIERSTRASS ; 
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_ECP_INVALID_KEY ; 
 int ecp_check_pubkey_mx (int /*<<< orphan*/  const*,TYPE_1__ const*) ; 
 int ecp_check_pubkey_sw (int /*<<< orphan*/  const*,TYPE_1__ const*) ; 
 scalar_t__ ecp_get_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int) ; 

int mbedtls_ecp_check_pubkey( const mbedtls_ecp_group *grp, const mbedtls_ecp_point *pt )
{
    /* Must use affine coordinates */
    if( mbedtls_mpi_cmp_int( &pt->Z, 1 ) != 0 )
        return( MBEDTLS_ERR_ECP_INVALID_KEY );

#if defined(ECP_MONTGOMERY)
    if( ecp_get_type( grp ) == ECP_TYPE_MONTGOMERY )
        return( ecp_check_pubkey_mx( grp, pt ) );
#endif
#if defined(ECP_SHORTWEIERSTRASS)
    if( ecp_get_type( grp ) == ECP_TYPE_SHORT_WEIERSTRASS )
        return( ecp_check_pubkey_sw( grp, pt ) );
#endif
    return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );
}