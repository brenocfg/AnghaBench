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
typedef  scalar_t__ mpi_limb_t ;
struct TYPE_3__ {unsigned int nlimbs; scalar_t__* d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 scalar_t__ BITS_PER_MPI_LIMB ; 
 int /*<<< orphan*/  count_trailing_zeros (unsigned int,scalar_t__) ; 

unsigned
mpi_trailing_zeros( const MPI a )
{
    unsigned n, count = 0;

    for(n=0; n < a->nlimbs; n++ ) {
	if( a->d[n] ) {
	    unsigned nn;
	    mpi_limb_t alimb = a->d[n];

	    count_trailing_zeros( nn, alimb );
	    count += nn;
	    break;
	}
	count += BITS_PER_MPI_LIMB;
    }
    return count;

}