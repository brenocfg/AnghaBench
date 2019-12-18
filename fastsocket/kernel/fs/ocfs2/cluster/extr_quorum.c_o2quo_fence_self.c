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
 int /*<<< orphan*/  emergency_restart () ; 
 int /*<<< orphan*/  o2hb_stop_all_regions () ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void o2quo_fence_self(void)
{
	/* panic spins with interrupts enabled.  with preempt
	 * threads can still schedule, etc, etc */
	o2hb_stop_all_regions();

	printk("ocfs2 is very sorry to be fencing this system by restarting\n");
	emergency_restart();
}