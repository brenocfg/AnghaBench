#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct subchannel {int /*<<< orphan*/  lock; int /*<<< orphan*/  schid; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_3__* private; TYPE_1__ dev; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_5__ {int resuming; } ;
struct TYPE_6__ {scalar_t__ state; TYPE_2__ flags; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  path_new_mask; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_DISCONNECTED ; 
 scalar_t__ DEV_STATE_OFFLINE ; 
 scalar_t__ DEV_STATE_ONLINE ; 
 int /*<<< orphan*/  LPM_ANYPATH ; 
 int /*<<< orphan*/  ccw_device_recognition (struct ccw_device*) ; 
 int /*<<< orphan*/  cio_enable_subchannel (struct subchannel*,int /*<<< orphan*/ ) ; 
 scalar_t__ cio_is_console (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_complete_work () ; 
 int /*<<< orphan*/  css_schedule_eval (int /*<<< orphan*/ ) ; 
 scalar_t__ dev_fsm_final_state (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __ccw_device_pm_restore(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);

	spin_lock_irq(sch->lock);
	if (cio_is_console(sch->schid)) {
		cio_enable_subchannel(sch, (u32)(addr_t)sch);
		goto out_unlock;
	}
	/*
	 * While we were sleeping, devices may have gone or become
	 * available again. Kick re-detection.
	 */
	cdev->private->flags.resuming = 1;
	cdev->private->path_new_mask = LPM_ANYPATH;
	css_schedule_eval(sch->schid);
	spin_unlock_irq(sch->lock);
	css_complete_work();

	/* cdev may have been moved to a different subchannel. */
	sch = to_subchannel(cdev->dev.parent);
	spin_lock_irq(sch->lock);
	if (cdev->private->state != DEV_STATE_ONLINE &&
	    cdev->private->state != DEV_STATE_OFFLINE)
		goto out_unlock;

	ccw_device_recognition(cdev);
	spin_unlock_irq(sch->lock);
	wait_event(cdev->private->wait_q, dev_fsm_final_state(cdev) ||
		   cdev->private->state == DEV_STATE_DISCONNECTED);
	spin_lock_irq(sch->lock);

out_unlock:
	cdev->private->flags.resuming = 0;
	spin_unlock_irq(sch->lock);
}