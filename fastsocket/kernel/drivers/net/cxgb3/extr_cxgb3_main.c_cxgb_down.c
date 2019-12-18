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
struct adapter {int /*<<< orphan*/  work_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb3_wq ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq_resources (struct adapter*) ; 
 int /*<<< orphan*/  quiesce_rx (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_intr_disable (struct adapter*) ; 
 int /*<<< orphan*/  t3_sge_stop (struct adapter*) ; 

__attribute__((used)) static void cxgb_down(struct adapter *adapter, int on_wq)
{
	t3_sge_stop(adapter);
	spin_lock_irq(&adapter->work_lock);	/* sync with PHY intr task */
	t3_intr_disable(adapter);
	spin_unlock_irq(&adapter->work_lock);

	free_irq_resources(adapter);
	quiesce_rx(adapter);
	t3_sge_stop(adapter);
	if (!on_wq)
		flush_workqueue(cxgb3_wq);/* wait for external IRQ handler */
}