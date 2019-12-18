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
typedef  int /*<<< orphan*/  mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_ERR_DHM_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_int (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int dhm_check_range( const mbedtls_mpi *param, const mbedtls_mpi *P )
{
    mbedtls_mpi L, U;
    int ret = MBEDTLS_ERR_DHM_BAD_INPUT_DATA;

    mbedtls_mpi_init( &L ); mbedtls_mpi_init( &U );

    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &L, 2 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &U, P, 2 ) );

    if( mbedtls_mpi_cmp_mpi( param, &L ) >= 0 &&
        mbedtls_mpi_cmp_mpi( param, &U ) <= 0 )
    {
        ret = 0;
    }

cleanup:
    mbedtls_mpi_free( &L ); mbedtls_mpi_free( &U );
    return( ret );
}