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
typedef  int /*<<< orphan*/ * mpi_ptr_t ;
typedef  scalar_t__ mpi_limb_t ;

/* Variables and functions */

mpi_limb_t
mpihelp_add_1( mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
	       mpi_size_t s1_size, mpi_limb_t s2_limb)
{
    mpi_limb_t x;

    x = *s1_ptr++;
    s2_limb += x;
    *res_ptr++ = s2_limb;
    if( s2_limb < x ) { /* sum is less than the left operand: handle carry */
	while( --s1_size ) {
	    x = *s1_ptr++ + 1;	/* add carry */
	    *res_ptr++ = x;	/* and store */
	    if( x )		/* not 0 (no overflow): we can stop */
		goto leave;
	}
	return 1; /* return carry (size of s1 to small) */
    }

  leave:
    if( res_ptr != s1_ptr ) { /* not the same variable */
	mpi_size_t i;	       /* copy the rest */
	for( i=0; i < s1_size-1; i++ )
	    res_ptr[i] = s1_ptr[i];
    }
    return 0; /* no carry */
}