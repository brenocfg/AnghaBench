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
struct TYPE_4__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mbedtls_ecp_copy( mbedtls_ecp_point *P, const mbedtls_ecp_point *Q )
{
    int ret;

    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &P->X, &Q->X ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &P->Y, &Q->Y ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &P->Z, &Q->Z ) );

cleanup:
    return( ret );
}