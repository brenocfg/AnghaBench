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
 int /*<<< orphan*/  oom_killer_enable () ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  thaw_tasks (int) ; 

void thaw_processes(void)
{
	oom_killer_enable();

	printk("Restarting tasks ... ");
	thaw_tasks(true);
	thaw_tasks(false);
	schedule();
	printk("done.\n");
}