#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int mbedtls_mpi_uint ;
struct TYPE_7__ {int* p; int n; int s; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_abs (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int fix_negative( mbedtls_mpi *N, signed char c, mbedtls_mpi *C, size_t bits )
{
    int ret;

    /* C = - c * 2^(bits + 32) */
#if !defined(MBEDTLS_HAVE_INT64)
    ((void) bits);
#else
    if( bits == 224 )
        C->p[ C->n - 1 ] = ((mbedtls_mpi_uint) -c) << 32;
    else
#endif
        C->p[ C->n - 1 ] = (mbedtls_mpi_uint) -c;

    /* N = - ( C - N ) */
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_abs( N, C, N ) );
    N->s = -1;

cleanup:

    return( ret );
}