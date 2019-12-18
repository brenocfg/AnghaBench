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
struct adapter {int slow_intr_mask; int /*<<< orphan*/  work_lock; int /*<<< orphan*/  ext_intr_handler_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PL_INT_ENABLE0 ; 
 int F_T3DBG ; 
 int /*<<< orphan*/  cxgb3_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void t3_os_ext_intr_handler(struct adapter *adapter)
{
	/*
	 * Schedule a task to handle external interrupts as they may be slow
	 * and we use a mutex to protect MDIO registers.  We disable PHY
	 * interrupts in the meantime and let the task reenable them when
	 * it's done.
	 */
	spin_lock(&adapter->work_lock);
	if (adapter->slow_intr_mask) {
		adapter->slow_intr_mask &= ~F_T3DBG;
		t3_write_reg(adapter, A_PL_INT_ENABLE0,
			     adapter->slow_intr_mask);
		queue_work(cxgb3_wq, &adapter->ext_intr_handler_task);
	}
	spin_unlock(&adapter->work_lock);
}