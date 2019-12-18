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
struct TYPE_4__ {unsigned long* d; int nlimbs; scalar_t__ flags; scalar_t__ nbits; scalar_t__ sign; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ RESIZE_IF_NEEDED (TYPE_1__*,int) ; 

int mpi_set_ui(MPI w, unsigned long u)
{
	if (RESIZE_IF_NEEDED(w, 1) < 0)
		return -ENOMEM;
	w->d[0] = u;
	w->nlimbs = u? 1:0;
	w->sign = 0;
	w->nbits = 0;
	w->flags = 0;
	return 0;
}