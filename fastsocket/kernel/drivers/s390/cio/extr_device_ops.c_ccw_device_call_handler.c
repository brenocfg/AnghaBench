#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct subchannel {int dummy; } ;
struct irb {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_3__* private; int /*<<< orphan*/  (* handler ) (struct ccw_device*,int /*<<< orphan*/ ,TYPE_4__*) ;TYPE_1__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  scsw; } ;
struct TYPE_7__ {scalar_t__ fast; int /*<<< orphan*/  repall; } ;
struct TYPE_8__ {TYPE_4__ irb; int /*<<< orphan*/  intparm; TYPE_2__ options; } ;

/* Variables and functions */
 unsigned int SCSW_STCTL_ALERT_STATUS ; 
 unsigned int SCSW_STCTL_INTER_STATUS ; 
 unsigned int SCSW_STCTL_PRIM_STATUS ; 
 unsigned int SCSW_STCTL_SEC_STATUS ; 
 unsigned int SCSW_STCTL_STATUS_PEND ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 unsigned int scsw_stctl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

int
ccw_device_call_handler(struct ccw_device *cdev)
{
	struct subchannel *sch;
	unsigned int stctl;
	int ending_status;

	sch = to_subchannel(cdev->dev.parent);

	/*
	 * we allow for the device action handler if .
	 *  - we received ending status
	 *  - the action handler requested to see all interrupts
	 *  - we received an intermediate status
	 *  - fast notification was requested (primary status)
	 *  - unsolicited interrupts
	 */
	stctl = scsw_stctl(&cdev->private->irb.scsw);
	ending_status = (stctl & SCSW_STCTL_SEC_STATUS) ||
		(stctl == (SCSW_STCTL_ALERT_STATUS | SCSW_STCTL_STATUS_PEND)) ||
		(stctl == SCSW_STCTL_STATUS_PEND);
	if (!ending_status &&
	    !cdev->private->options.repall &&
	    !(stctl & SCSW_STCTL_INTER_STATUS) &&
	    !(cdev->private->options.fast &&
	      (stctl & SCSW_STCTL_PRIM_STATUS)))
		return 0;

	/* Clear pending timers for device driver initiated I/O. */
	if (ending_status)
		ccw_device_set_timeout(cdev, 0);
	/*
	 * Now we are ready to call the device driver interrupt handler.
	 */
	if (cdev->handler)
		cdev->handler(cdev, cdev->private->intparm,
			      &cdev->private->irb);

	/*
	 * Clear the old and now useless interrupt response block.
	 */
	memset(&cdev->private->irb, 0, sizeof(struct irb));

	return 1;
}