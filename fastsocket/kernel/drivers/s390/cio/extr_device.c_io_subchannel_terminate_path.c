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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__ lpum; } ;
struct TYPE_5__ {TYPE_1__ pmcw; int /*<<< orphan*/  scsw; } ;
struct subchannel {TYPE_2__ schib; } ;
struct ccw_device {TYPE_3__* private; } ;
struct TYPE_6__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_EVENT_NOTOPER ; 
 int /*<<< orphan*/  DEV_EVENT_VERIFY ; 
 scalar_t__ DEV_STATE_ONLINE ; 
 int /*<<< orphan*/  ccw_device_kill_io (struct ccw_device*) ; 
 scalar_t__ cio_clear (struct subchannel*) ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 int /*<<< orphan*/  dev_fsm_event (struct ccw_device*,int /*<<< orphan*/ ) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 
 scalar_t__ scsw_actl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_subchannel_terminate_path(struct subchannel *sch, u8 mask)
{
	struct ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	if (!cdev)
		return;
	if (cio_update_schib(sch))
		goto err;
	/* Check for I/O on path. */
	if (scsw_actl(&sch->schib.scsw) == 0 || sch->schib.pmcw.lpum != mask)
		goto out;
	if (cdev->private->state == DEV_STATE_ONLINE) {
		ccw_device_kill_io(cdev);
		goto out;
	}
	if (cio_clear(sch))
		goto err;
out:
	/* Trigger path verification. */
	dev_fsm_event(cdev, DEV_EVENT_VERIFY);
	return;

err:
	dev_fsm_event(cdev, DEV_EVENT_NOTOPER);
}