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
struct adapter {int slow_intr_mask; int /*<<< orphan*/  ext_intr_handler_task; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_PL_ENABLE ; 
 int F_PL_INTR_EXT ; 
 int F_PL_INTR_SGE_DATA ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void t1_elmer0_ext_intr(struct adapter *adapter)
{
	/*
	 * Schedule a task to handle external interrupts as we require
	 * a process context.  We disable EXT interrupts in the interim
	 * and let the task reenable them when it's done.
	 */
	adapter->slow_intr_mask &= ~F_PL_INTR_EXT;
	writel(adapter->slow_intr_mask | F_PL_INTR_SGE_DATA,
		   adapter->regs + A_PL_ENABLE);
	schedule_work(&adapter->ext_intr_handler_task);
}