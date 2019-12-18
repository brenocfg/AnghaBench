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
typedef  int /*<<< orphan*/  mbedtls_mpi ;
struct TYPE_5__ {int /*<<< orphan*/  Y; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
struct TYPE_6__ {int /*<<< orphan*/  P; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_safe_cond_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecp_safe_invert_jac( const mbedtls_ecp_group *grp,
                            mbedtls_ecp_point *Q,
                            unsigned char inv )
{
    int ret;
    unsigned char nonzero;
    mbedtls_mpi mQY;

    mbedtls_mpi_init( &mQY );

    /* Use the fact that -Q.Y mod P = P - Q.Y unless Q.Y == 0 */
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &mQY, &grp->P, &Q->Y ) );
    nonzero = mbedtls_mpi_cmp_int( &Q->Y, 0 ) != 0;
    MBEDTLS_MPI_CHK( mbedtls_mpi_safe_cond_assign( &Q->Y, &mQY, inv & nonzero ) );

cleanup:
    mbedtls_mpi_free( &mQY );

    return( ret );
}