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
struct TYPE_5__ {int sign; int /*<<< orphan*/  flags; int /*<<< orphan*/  nbits; scalar_t__ nlimbs; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MPN_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RESIZE_IF_NEEDED (TYPE_1__*,size_t) ; 

int mpi_set(MPI w, const MPI u)
{
	mpi_ptr_t wp, up;
	mpi_size_t usize = u->nlimbs;
	int usign = u->sign;

	if (RESIZE_IF_NEEDED(w, (size_t) usize) < 0)
		return -ENOMEM;

	wp = w->d;
	up = u->d;
	MPN_COPY(wp, up, usize);
	w->nlimbs = usize;
	w->nbits = u->nbits;
	w->flags = u->flags;
	w->sign = usign;
	return 0;
}