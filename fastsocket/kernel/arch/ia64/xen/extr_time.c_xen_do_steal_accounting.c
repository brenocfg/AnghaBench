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

/* Variables and functions */
 unsigned long consider_steal_time (unsigned long) ; 
 int /*<<< orphan*/  ia64_get_itc () ; 
 scalar_t__ time_after (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xen_do_steal_accounting(unsigned long *new_itm)
{
	unsigned long delta_itm;
	delta_itm = consider_steal_time(*new_itm);
	*new_itm += delta_itm;
	if (time_after(*new_itm, ia64_get_itc()) && delta_itm)
		return 1;

	return 0;
}