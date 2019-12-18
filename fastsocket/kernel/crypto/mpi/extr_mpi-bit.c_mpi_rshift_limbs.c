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
typedef  unsigned int mpi_size_t ;
typedef  scalar_t__* mpi_ptr_t ;
struct TYPE_3__ {unsigned int nlimbs; scalar_t__* d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */

void
mpi_rshift_limbs( MPI a, unsigned int count )
{
    mpi_ptr_t ap = a->d;
    mpi_size_t n = a->nlimbs;
    unsigned int i;

    if( count >= n ) {
	a->nlimbs = 0;
	return;
    }

    for( i = 0; i < n - count; i++ )
	ap[i] = ap[i+count];
    ap[i] = 0;
    a->nlimbs -= count;
}