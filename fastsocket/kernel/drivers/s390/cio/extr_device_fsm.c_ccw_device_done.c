#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sch_no; } ;
struct subchannel {TYPE_3__ schid; } ;
struct irb {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_5__* private; int /*<<< orphan*/  online; TYPE_1__ dev; } ;
struct TYPE_9__ {scalar_t__ donotify; } ;
struct TYPE_7__ {int /*<<< orphan*/  devno; } ;
struct TYPE_10__ {int state; int /*<<< orphan*/  wait_q; TYPE_4__ flags; TYPE_2__ dev_id; int /*<<< orphan*/  irb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDEV_TODO_UNREG ; 
 int /*<<< orphan*/  CIO_BOXED ; 
 int /*<<< orphan*/  CIO_GONE ; 
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIO_NO_PATH ; 
#define  DEV_STATE_BOXED 130 
#define  DEV_STATE_DISCONNECTED 129 
#define  DEV_STATE_NOT_OPER 128 
 int DEV_STATE_ONLINE ; 
 int /*<<< orphan*/  NOTIFY_OK ; 
 int /*<<< orphan*/  ccw_device_notify (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_oper_notify (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_sched_todo (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_set_disconnected (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cio_disable_subchannel (struct subchannel*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ccw_device_done(struct ccw_device *cdev, int state)
{
	struct subchannel *sch;

	sch = to_subchannel(cdev->dev.parent);

	ccw_device_set_timeout(cdev, 0);

	if (state != DEV_STATE_ONLINE)
		cio_disable_subchannel(sch);

	/* Reset device status. */
	memset(&cdev->private->irb, 0, sizeof(struct irb));

	cdev->private->state = state;

	switch (state) {
	case DEV_STATE_BOXED:
		CIO_MSG_EVENT(0, "Boxed device %04x on subchannel %04x\n",
			      cdev->private->dev_id.devno, sch->schid.sch_no);
		if (cdev->online &&
		    ccw_device_notify(cdev, CIO_BOXED) != NOTIFY_OK)
			ccw_device_sched_todo(cdev, CDEV_TODO_UNREG);
		cdev->private->flags.donotify = 0;
		break;
	case DEV_STATE_NOT_OPER:
		CIO_MSG_EVENT(0, "Device %04x gone on subchannel %04x\n",
			      cdev->private->dev_id.devno, sch->schid.sch_no);
		if (ccw_device_notify(cdev, CIO_GONE) != NOTIFY_OK)
			ccw_device_sched_todo(cdev, CDEV_TODO_UNREG);
		else
			ccw_device_set_disconnected(cdev);
		cdev->private->flags.donotify = 0;
		break;
	case DEV_STATE_DISCONNECTED:
		CIO_MSG_EVENT(0, "Disconnected device %04x on subchannel "
			      "%04x\n", cdev->private->dev_id.devno,
			      sch->schid.sch_no);
		if (ccw_device_notify(cdev, CIO_NO_PATH) != NOTIFY_OK)
			ccw_device_sched_todo(cdev, CDEV_TODO_UNREG);
		else
			ccw_device_set_disconnected(cdev);
		cdev->private->flags.donotify = 0;
		break;
	default:
		break;
	}

	if (cdev->private->flags.donotify) {
		cdev->private->flags.donotify = 0;
		ccw_device_oper_notify(cdev);
	}
	wake_up(&cdev->private->wait_q);
}