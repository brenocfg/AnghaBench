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
typedef  size_t mbedtls_mpi_uint ;
struct TYPE_4__ {size_t n; size_t* p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 size_t biL ; 
 int /*<<< orphan*/  mbedtls_mpi_grow (TYPE_1__*,size_t) ; 

int mbedtls_mpi_set_bit( mbedtls_mpi *X, size_t pos, unsigned char val )
{
    int ret = 0;
    size_t off = pos / biL;
    size_t idx = pos % biL;

    if( val != 0 && val != 1 )
        return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    if( X->n * biL <= pos )
    {
        if( val == 0 )
            return( 0 );

        MBEDTLS_MPI_CHK( mbedtls_mpi_grow( X, off + 1 ) );
    }

    X->p[off] &= ~( (mbedtls_mpi_uint) 0x01 << idx );
    X->p[off] |= (mbedtls_mpi_uint) val << idx;

cleanup:

    return( ret );
}