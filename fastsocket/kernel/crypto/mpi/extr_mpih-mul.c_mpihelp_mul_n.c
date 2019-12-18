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
typedef  int mpi_size_t ;
typedef  scalar_t__ mpi_ptr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int KARATSUBA_THRESHOLD ; 
 scalar_t__ mpi_alloc_limb_space (int) ; 
 int /*<<< orphan*/  mpi_free_limb_space (scalar_t__) ; 
 int /*<<< orphan*/  mpih_sqr_n (scalar_t__,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  mpih_sqr_n_basecase (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  mul_n (scalar_t__,scalar_t__,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  mul_n_basecase (scalar_t__,scalar_t__,scalar_t__,int) ; 

int
mpihelp_mul_n( mpi_ptr_t prodp, mpi_ptr_t up, mpi_ptr_t vp, mpi_size_t size)
{
    if( up == vp ) {
	if( size < KARATSUBA_THRESHOLD )
	    mpih_sqr_n_basecase( prodp, up, size );
	else {
	    mpi_ptr_t tspace;
	    tspace = mpi_alloc_limb_space( 2 * size );
	    if (!tspace)
		    return -ENOMEM;
	    mpih_sqr_n( prodp, up, size, tspace );
	    mpi_free_limb_space( tspace );
	}
    }
    else {
	if( size < KARATSUBA_THRESHOLD )
	    mul_n_basecase( prodp, up, vp, size );
	else {
	    mpi_ptr_t tspace;
	    tspace = mpi_alloc_limb_space( 2 * size );
	    if (!tspace)
		    return -ENOMEM;
	    mul_n (prodp, up, vp, size, tspace);
	    mpi_free_limb_space( tspace );
	}
    }

    return 0;
}