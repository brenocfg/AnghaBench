#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (int /*<<< orphan*/ *,int) ; 

int mbedtls_ecp_set_zero( mbedtls_ecp_point *pt )
{
    int ret;

    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &pt->X , 1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &pt->Y , 1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &pt->Z , 0 ) );

cleanup:
    return( ret );
}