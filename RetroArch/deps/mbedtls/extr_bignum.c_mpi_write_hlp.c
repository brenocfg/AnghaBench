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
typedef  int mbedtls_mpi_uint ;
typedef  int /*<<< orphan*/  mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mbedtls_mpi_div_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mbedtls_mpi_mod_int (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mpi_write_hlp( mbedtls_mpi *X, int radix, char **p )
{
    int ret;
    mbedtls_mpi_uint r;

    if( radix < 2 || radix > 16 )
        return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_int( &r, X, radix ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_div_int( X, NULL, X, radix ) );

    if( mbedtls_mpi_cmp_int( X, 0 ) != 0 )
        MBEDTLS_MPI_CHK( mpi_write_hlp( X, radix, p ) );

    if( r < 10 )
        *(*p)++ = (char)( r + 0x30 );
    else
        *(*p)++ = (char)( r + 0x37 );

cleanup:

    return( ret );
}