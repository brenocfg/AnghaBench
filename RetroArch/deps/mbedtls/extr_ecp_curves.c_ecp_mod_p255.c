#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mbedtls_mpi_uint ;
struct TYPE_10__ {int n; int s; scalar_t__* p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int P255_WIDTH ; 
 int /*<<< orphan*/  mbedtls_mpi_add_abs (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_int (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_set_bit (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_shift_r (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ecp_mod_p255( mbedtls_mpi *N )
{
    int ret;
    size_t i;
    mbedtls_mpi M;
    mbedtls_mpi_uint Mp[P255_WIDTH + 2];

    if( N->n < P255_WIDTH )
        return( 0 );

    /* M = A1 */
    M.s = 1;
    M.n = N->n - ( P255_WIDTH - 1 );
    if( M.n > P255_WIDTH + 1 )
        M.n = P255_WIDTH + 1;
    M.p = Mp;
    memset( Mp, 0, sizeof Mp );
    memcpy( Mp, N->p + P255_WIDTH - 1, M.n * sizeof( mbedtls_mpi_uint ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &M, 255 % ( 8 * sizeof( mbedtls_mpi_uint ) ) ) );
    M.n++; /* Make room for multiplication by 19 */

    /* N = A0 */
    MBEDTLS_MPI_CHK( mbedtls_mpi_set_bit( N, 255, 0 ) );
    for( i = P255_WIDTH; i < N->n; i++ )
        N->p[i] = 0;

    /* N = A0 + 19 * A1 */
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_int( &M, &M, 19 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_add_abs( N, N, &M ) );

cleanup:
    return( ret );
}