#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ s; } ;
typedef  TYPE_1__ mbedtls_mpi ;
struct TYPE_16__ {int pbits; int /*<<< orphan*/  P; int /*<<< orphan*/  (* modp ) (TYPE_1__*) ;} ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_add_mpi (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mbedtls_mpi_bitlen (TYPE_1__*) ; 
 scalar_t__ mbedtls_mpi_cmp_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mbedtls_mpi_mod_mpi (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_abs (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int ecp_modp( mbedtls_mpi *N, const mbedtls_ecp_group *grp )
{
    int ret;

    if( grp->modp == NULL )
        return( mbedtls_mpi_mod_mpi( N, N, &grp->P ) );

    /* N->s < 0 is a much faster test, which fails only if N is 0 */
    if( ( N->s < 0 && mbedtls_mpi_cmp_int( N, 0 ) != 0 ) ||
        mbedtls_mpi_bitlen( N ) > 2 * grp->pbits )
    {
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );
    }

    MBEDTLS_MPI_CHK( grp->modp( N ) );

    /* N->s < 0 is a much faster test, which fails only if N is 0 */
    while( N->s < 0 && mbedtls_mpi_cmp_int( N, 0 ) != 0 )
        MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( N, N, &grp->P ) );

    while( mbedtls_mpi_cmp_mpi( N, &grp->P ) >= 0 )
        /* we known P, N and the result are positive */
        MBEDTLS_MPI_CHK( mbedtls_mpi_sub_abs( N, N, &grp->P ) );

cleanup:
    return( ret );
}