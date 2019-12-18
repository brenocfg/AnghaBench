#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;
struct TYPE_11__ {int /*<<< orphan*/  const Y; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
struct TYPE_12__ {int /*<<< orphan*/  P; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ecp_copy (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_ecp_mul (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int mbedtls_ecp_mul_shortcuts( mbedtls_ecp_group *grp,
                                      mbedtls_ecp_point *R,
                                      const mbedtls_mpi *m,
                                      const mbedtls_ecp_point *P )
{
    int ret;

    if( mbedtls_mpi_cmp_int( m, 1 ) == 0 )
    {
        MBEDTLS_MPI_CHK( mbedtls_ecp_copy( R, P ) );
    }
    else if( mbedtls_mpi_cmp_int( m, -1 ) == 0 )
    {
        MBEDTLS_MPI_CHK( mbedtls_ecp_copy( R, P ) );
        if( mbedtls_mpi_cmp_int( &R->Y, 0 ) != 0 )
            MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &R->Y, &grp->P, &R->Y ) );
    }
    else
    {
        MBEDTLS_MPI_CHK( mbedtls_ecp_mul( grp, R, m, P, NULL, NULL ) );
    }

cleanup:
    return( ret );
}