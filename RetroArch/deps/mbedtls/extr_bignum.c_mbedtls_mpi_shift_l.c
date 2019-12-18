#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t mbedtls_mpi_uint ;
struct TYPE_5__ {size_t n; size_t* p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LIMBS (size_t) ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 size_t biL ; 
 size_t mbedtls_mpi_bitlen (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_grow (TYPE_1__*,int /*<<< orphan*/ ) ; 

int mbedtls_mpi_shift_l( mbedtls_mpi *X, size_t count )
{
    int ret;
    size_t i, v0, t1;
    mbedtls_mpi_uint r0 = 0, r1;

    v0 = count / (biL    );
    t1 = count & (biL - 1);

    i = mbedtls_mpi_bitlen( X ) + count;

    if( X->n * biL < i )
        MBEDTLS_MPI_CHK( mbedtls_mpi_grow( X, BITS_TO_LIMBS( i ) ) );

    ret = 0;

    /*
     * shift by count / limb_size
     */
    if( v0 > 0 )
    {
        for( i = X->n; i > v0; i-- )
            X->p[i - 1] = X->p[i - v0 - 1];

        for( ; i > 0; i-- )
            X->p[i - 1] = 0;
    }

    /*
     * shift by count % limb_size
     */
    if( t1 > 0 )
    {
        for( i = v0; i < X->n; i++ )
        {
            r1 = X->p[i] >> (biL - t1);
            X->p[i] <<= t1;
            X->p[i] |= r0;
            r0 = r1;
        }
    }

cleanup:

    return( ret );
}