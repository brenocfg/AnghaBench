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
struct workqueue_struct {int dummy; } ;
struct MPT2SAS_ADAPTER {int /*<<< orphan*/  fault_reset_work; int /*<<< orphan*/  ioc_reset_in_progress_lock; struct workqueue_struct* fault_reset_work_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  flush_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
mpt2sas_base_stop_watchdog(struct MPT2SAS_ADAPTER *ioc)
{
	unsigned long	 flags;
	struct workqueue_struct *wq;

	spin_lock_irqsave(&ioc->ioc_reset_in_progress_lock, flags);
	wq = ioc->fault_reset_work_q;
	ioc->fault_reset_work_q = NULL;
	spin_unlock_irqrestore(&ioc->ioc_reset_in_progress_lock, flags);
	if (wq) {
		if (!cancel_delayed_work(&ioc->fault_reset_work))
			flush_workqueue(wq);
		destroy_workqueue(wq);
	}
}