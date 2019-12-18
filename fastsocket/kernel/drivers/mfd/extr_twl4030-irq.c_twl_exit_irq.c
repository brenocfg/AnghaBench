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
 int ENOSYS ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ twl4030_irq_base ; 

int twl_exit_irq(void)
{
	/* FIXME undo twl_init_irq() */
	if (twl4030_irq_base) {
		pr_err("twl4030: can't yet clean up IRQs?\n");
		return -ENOSYS;
	}
	return 0;
}