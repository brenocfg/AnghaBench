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
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  lv1_pause (int) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 

void ps3_sys_manager_halt(void)
{
	pr_emerg("System Halted, OK to turn off power\n");
	local_irq_disable();
	while (1)
		lv1_pause(1);
}