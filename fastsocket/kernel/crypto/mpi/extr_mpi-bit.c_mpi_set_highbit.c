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
struct TYPE_4__ {unsigned int nlimbs; unsigned int alloced; unsigned int* d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 unsigned int A_LIMB_1 ; 
 unsigned int BITS_PER_MPI_LIMB ; 
 int ENOMEM ; 
 scalar_t__ mpi_resize (TYPE_1__*,unsigned int) ; 

int
mpi_set_highbit( MPI a, unsigned n )
{
    unsigned limbno, bitno;

    limbno = n / BITS_PER_MPI_LIMB;
    bitno  = n % BITS_PER_MPI_LIMB;

    if( limbno >= a->nlimbs ) { /* resize */
	if( a->alloced >= limbno )
	    if (mpi_resize(a, limbno+1 ) < 0) return -ENOMEM;
	a->nlimbs = limbno+1;
    }
    a->d[limbno] |= (A_LIMB_1<<bitno);
    for( bitno++; bitno < BITS_PER_MPI_LIMB; bitno++ )
	a->d[limbno] &= ~(A_LIMB_1 << bitno);
    a->nlimbs = limbno+1;
    return 0;
}