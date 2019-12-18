#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* clock_t ;
struct TYPE_5__ {TYPE_1__* cl_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* c_init ) () ;} ;

/* Variables and functions */
 int clock_count ; 
 TYPE_2__* clock_list ; 
 int /*<<< orphan*/  stub1 () ; 

void
clock_oldinit(void)
{
	clock_t			clock;
	int	i;

	/*
	 * Initialize basic clock structures.
	 */
	for (i = 0; i < clock_count; i++) {
		clock = &clock_list[i];
		if (clock->cl_ops && clock->cl_ops->c_init)
			(*clock->cl_ops->c_init)();
	}
}