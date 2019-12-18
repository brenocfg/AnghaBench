#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;
struct TYPE_4__ {int nbits; int /*<<< orphan*/  N; } ;
typedef  TYPE_1__ mbedtls_ecp_group ;

/* Variables and functions */
 scalar_t__ ECP_TYPE_MONTGOMERY ; 
 scalar_t__ ECP_TYPE_SHORT_WEIERSTRASS ; 
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_ECP_INVALID_KEY ; 
 scalar_t__ ecp_get_type (TYPE_1__ const*) ; 
 int mbedtls_mpi_bitlen (int /*<<< orphan*/  const*) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mpi_get_bit (int /*<<< orphan*/  const*,int) ; 

int mbedtls_ecp_check_privkey( const mbedtls_ecp_group *grp, const mbedtls_mpi *d )
{
#if defined(ECP_MONTGOMERY)
    if( ecp_get_type( grp ) == ECP_TYPE_MONTGOMERY )
    {
        /* see [Curve25519] page 5 */
        if( mbedtls_mpi_get_bit( d, 0 ) != 0 ||
            mbedtls_mpi_get_bit( d, 1 ) != 0 ||
            mbedtls_mpi_get_bit( d, 2 ) != 0 ||
            mbedtls_mpi_bitlen( d ) - 1 != grp->nbits ) /* mbedtls_mpi_bitlen is one-based! */
            return( MBEDTLS_ERR_ECP_INVALID_KEY );
        else
            return( 0 );
    }
#endif /* ECP_MONTGOMERY */
#if defined(ECP_SHORTWEIERSTRASS)
    if( ecp_get_type( grp ) == ECP_TYPE_SHORT_WEIERSTRASS )
    {
        /* see SEC1 3.2 */
        if( mbedtls_mpi_cmp_int( d, 1 ) < 0 ||
            mbedtls_mpi_cmp_mpi( d, &grp->N ) >= 0 )
            return( MBEDTLS_ERR_ECP_INVALID_KEY );
        else
            return( 0 );
    }
#endif /* ECP_SHORTWEIERSTRASS */

    return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );
}