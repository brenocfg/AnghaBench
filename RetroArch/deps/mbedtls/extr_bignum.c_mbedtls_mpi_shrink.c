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
typedef  scalar_t__ mbedtls_mpi_uint ;
struct TYPE_4__ {size_t n; scalar_t__* p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_ALLOC_FAILED ; 
 size_t ciL ; 
 scalar_t__ mbedtls_calloc (size_t,size_t) ; 
 int /*<<< orphan*/  mbedtls_free (scalar_t__*) ; 
 int mbedtls_mpi_grow (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  mbedtls_mpi_zeroize (scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,size_t) ; 

int mbedtls_mpi_shrink( mbedtls_mpi *X, size_t nblimbs )
{
    mbedtls_mpi_uint *p;
    size_t i;

    /* Actually resize up in this case */
    if( X->n <= nblimbs )
        return( mbedtls_mpi_grow( X, nblimbs ) );

    for( i = X->n - 1; i > 0; i-- )
        if( X->p[i] != 0 )
            break;
    i++;

    if( i < nblimbs )
        i = nblimbs;

    if( ( p = (mbedtls_mpi_uint*)mbedtls_calloc( i, ciL ) ) == NULL )
        return( MBEDTLS_ERR_MPI_ALLOC_FAILED );

    if( X->p != NULL )
    {
        memcpy( p, X->p, i * ciL );
        mbedtls_mpi_zeroize( X->p, X->n );
        mbedtls_free( X->p );
    }

    X->n = i;
    X->p = p;

    return( 0 );
}