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
typedef  int mbedtls_mpi_uint ;
typedef  int mbedtls_mpi_sint ;
struct TYPE_3__ {int* p; size_t n; scalar_t__ s; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_DIVISION_BY_ZERO ; 
 int MBEDTLS_ERR_MPI_NEGATIVE_VALUE ; 
 int biH ; 

int mbedtls_mpi_mod_int( mbedtls_mpi_uint *r, const mbedtls_mpi *A, mbedtls_mpi_sint b )
{
    size_t i;
    mbedtls_mpi_uint x, y, z;

    if( b == 0 )
        return( MBEDTLS_ERR_MPI_DIVISION_BY_ZERO );

    if( b < 0 )
        return( MBEDTLS_ERR_MPI_NEGATIVE_VALUE );

    /*
     * handle trivial cases
     */
    if( b == 1 )
    {
        *r = 0;
        return( 0 );
    }

    if( b == 2 )
    {
        *r = A->p[0] & 1;
        return( 0 );
    }

    /*
     * general case
     */
    for( i = A->n, y = 0; i > 0; i-- )
    {
        x  = A->p[i - 1];
        y  = ( y << biH ) | ( x >> biH );
        z  = y / b;
        y -= z * b;

        x <<= biH;
        y  = ( y << biH ) | ( x >> biH );
        z  = y / b;
        y -= z * b;
    }

    /*
     * If A is negative, then the current y represents a negative value.
     * Flipping it to the positive side.
     */
    if( A->s < 0 && y != 0 )
        y = b - y;

    *r = y;

    return( 0 );
}