#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct adapter {int tid_release_task_busy; int flags; TYPE_2__* pdev; TYPE_1__* msix_info; int /*<<< orphan*/ * tid_release_head; int /*<<< orphan*/  db_drop_task; int /*<<< orphan*/  db_full_task; int /*<<< orphan*/  tid_release_task; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  vec; } ;

/* Variables and functions */
 int FULL_INIT_DONE ; 
 int USING_MSIX ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adapter*) ; 
 int /*<<< orphan*/  free_msix_queue_irqs (struct adapter*) ; 
 int /*<<< orphan*/  quiesce_rx (struct adapter*) ; 
 int /*<<< orphan*/  t4_free_sge_resources (struct adapter*) ; 
 int /*<<< orphan*/  t4_intr_disable (struct adapter*) ; 
 int /*<<< orphan*/  t4_sge_stop (struct adapter*) ; 

__attribute__((used)) static void cxgb_down(struct adapter *adapter)
{
	t4_intr_disable(adapter);
	cancel_work_sync(&adapter->tid_release_task);
	cancel_work_sync(&adapter->db_full_task);
	cancel_work_sync(&adapter->db_drop_task);
	adapter->tid_release_task_busy = false;
	adapter->tid_release_head = NULL;

	if (adapter->flags & USING_MSIX) {
		free_msix_queue_irqs(adapter);
		free_irq(adapter->msix_info[0].vec, adapter);
	} else
		free_irq(adapter->pdev->irq, adapter);
	quiesce_rx(adapter);
	t4_sge_stop(adapter);
	t4_free_sge_resources(adapter);
	adapter->flags &= ~FULL_INIT_DONE;
}