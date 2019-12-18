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
typedef  int /*<<< orphan*/  mpi_ptr_t ;
struct TYPE_5__ {scalar_t__ nlimbs; int /*<<< orphan*/  d; int /*<<< orphan*/  sign; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MPN_NORMALIZE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RESIZE_IF_NEEDED (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  mpihelp_rshift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

int
mpi_rshift( MPI x, MPI a, unsigned n )
{
    mpi_ptr_t xp;
    mpi_size_t xsize;

    xsize = a->nlimbs;
    x->sign = a->sign;
    if (RESIZE_IF_NEEDED(x, (size_t)xsize) < 0) return -ENOMEM;
    xp = x->d;

    if( xsize ) {
	mpihelp_rshift( xp, a->d, xsize, n);
	MPN_NORMALIZE( xp, xsize);
    }
    x->nlimbs = xsize;
    return 0;
}