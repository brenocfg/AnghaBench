#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  const mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_NEGATIVE_VALUE ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_add_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_div_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int mbedtls_mpi_mod_mpi( mbedtls_mpi *R, const mbedtls_mpi *A, const mbedtls_mpi *B )
{
    int ret;

    if( mbedtls_mpi_cmp_int( B, 0 ) < 0 )
        return( MBEDTLS_ERR_MPI_NEGATIVE_VALUE );

    MBEDTLS_MPI_CHK( mbedtls_mpi_div_mpi( NULL, R, A, B ) );

    while( mbedtls_mpi_cmp_int( R, 0 ) < 0 )
      MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( R, R, B ) );

    while( mbedtls_mpi_cmp_mpi( R, B ) >= 0 )
      MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( R, R, B ) );

cleanup:

    return( ret );
}