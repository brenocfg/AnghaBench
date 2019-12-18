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
typedef  scalar_t__ mpi_size_t ;
typedef  scalar_t__* mpi_ptr_t ;
typedef  scalar_t__ mpi_limb_t ;
struct TYPE_5__ {scalar_t__ nlimbs; int sign; scalar_t__ alloced; scalar_t__* d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ mpi_resize (TYPE_1__*,scalar_t__) ; 
 scalar_t__ mpihelp_mul_1 (scalar_t__*,scalar_t__*,scalar_t__,scalar_t__) ; 

int
mpi_mul_ui( MPI prod, MPI mult, unsigned long small_mult )
{
    mpi_size_t size, prod_size;
    mpi_ptr_t  prod_ptr;
    mpi_limb_t cy;
    int sign;

    size = mult->nlimbs;
    sign = mult->sign;

    if( !size || !small_mult ) {
	prod->nlimbs = 0;
	prod->sign = 0;
	return 0;
    }

    prod_size = size + 1;
    if( prod->alloced < prod_size )
	    if (mpi_resize( prod, prod_size ) < 0)
		    return -ENOMEM;
    prod_ptr = prod->d;

    cy = mpihelp_mul_1( prod_ptr, mult->d, size, (mpi_limb_t)small_mult );
    if( cy )
	prod_ptr[size++] = cy;
    prod->nlimbs = size;
    prod->sign = sign;
    return 0;
}