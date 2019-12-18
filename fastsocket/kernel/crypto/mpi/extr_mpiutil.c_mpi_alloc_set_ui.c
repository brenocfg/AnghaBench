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
struct TYPE_4__ {unsigned long* d; int nlimbs; scalar_t__ sign; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 TYPE_1__* mpi_alloc (int) ; 

MPI mpi_alloc_set_ui(unsigned long u)
{
	MPI w = mpi_alloc(1);
	if (!w)
		return w;
	w->d[0] = u;
	w->nlimbs = u? 1:0;
	w->sign = 0;
	return w;
}