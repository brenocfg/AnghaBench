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
struct TYPE_5__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  Z; int /*<<< orphan*/  X; } ;
struct TYPE_6__ {int nbits; TYPE_1__ G; int /*<<< orphan*/  P; int /*<<< orphan*/  pbits; int /*<<< orphan*/  A; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_bitlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_read_string (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  mbedtls_mpi_shift_l (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ecp_use_curve25519( mbedtls_ecp_group *grp )
{
    int ret;

    /* Actually ( A + 2 ) / 4 */
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &grp->A, 16, "01DB42" ) );

    /* P = 2^255 - 19 */
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &grp->P, 1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_shift_l( &grp->P, 255 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &grp->P, &grp->P, 19 ) );
    grp->pbits = mbedtls_mpi_bitlen( &grp->P );

    /* Y intentionaly not set, since we use x/z coordinates.
     * This is used as a marker to identify Montgomery curves! */
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &grp->G.X, 9 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &grp->G.Z, 1 ) );
    mbedtls_mpi_free( &grp->G.Y );

    /* Actually, the required msb for private keys */
    grp->nbits = 254;

cleanup:
    if( ret != 0 )
        mbedtls_ecp_group_free( grp );

    return( ret );
}