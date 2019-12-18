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
struct subchannel {int /*<<< orphan*/  lock; int /*<<< orphan*/  todo_work; int /*<<< orphan*/  dev; } ;
struct eadm_private {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ EADM_IDLE ; 
 scalar_t__ EADM_NOT_OPER ; 
 int /*<<< orphan*/  SCH_TODO_UNREG ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 int /*<<< orphan*/  css_sched_sch_todo (struct subchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 struct eadm_private* get_eadm_private (struct subchannel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eadm_subchannel_sch_event(struct subchannel *sch, int process)
{
	struct eadm_private *private;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(sch->lock, flags);
	if (!device_is_registered(&sch->dev))
		goto out_unlock;

	if (work_pending(&sch->todo_work))
		goto out_unlock;

	if (cio_update_schib(sch)) {
		css_sched_sch_todo(sch, SCH_TODO_UNREG);
		goto out_unlock;
	}
	private = get_eadm_private(sch);
	if (private->state == EADM_NOT_OPER)
		private->state = EADM_IDLE;

out_unlock:
	spin_unlock_irqrestore(sch->lock, flags);

	return ret;
}