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
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {TYPE_4__ pmcw; } ;
struct TYPE_8__ {int /*<<< orphan*/  ssid; int /*<<< orphan*/  sch_no; } ;
struct subchannel {int /*<<< orphan*/  lock; TYPE_5__ schib; TYPE_3__ schid; int /*<<< orphan*/  todo_work; int /*<<< orphan*/  dev; } ;
struct ccw_device {int /*<<< orphan*/  dev; TYPE_2__* private; } ;
struct ccw_dev_id {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
typedef  enum io_sch_action { ____Placeholder_io_sch_action } io_sch_action ;
struct TYPE_6__ {int /*<<< orphan*/  resuming; } ;
struct TYPE_7__ {TYPE_1__ flags; int /*<<< orphan*/  state; int /*<<< orphan*/  todo_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DEV_EVENT_NOTOPER ; 
 int /*<<< orphan*/  DEV_STATE_SENSE_ID ; 
 int EAGAIN ; 
#define  IO_SCH_ATTACH 136 
#define  IO_SCH_DISC 135 
#define  IO_SCH_NOP 134 
#define  IO_SCH_ORPH_ATTACH 133 
#define  IO_SCH_ORPH_UNREG 132 
#define  IO_SCH_REPROBE 131 
#define  IO_SCH_UNREG 130 
#define  IO_SCH_UNREG_ATTACH 129 
#define  IO_SCH_VERIFY 128 
 int ccw_device_move_to_orph (struct ccw_device*) ; 
 int ccw_device_move_to_sch (struct ccw_device*,struct subchannel*) ; 
 int /*<<< orphan*/  ccw_device_set_disconnected (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_set_notoper (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_trigger_reprobe (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_unregister (struct ccw_device*) ; 
 int /*<<< orphan*/  css_sch_device_unregister (struct subchannel*) ; 
 int /*<<< orphan*/  dev_fsm_event (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 struct ccw_device* get_ccwdev_by_dev_id (struct ccw_dev_id*) ; 
 int /*<<< orphan*/  io_subchannel_verify (struct subchannel*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sch_create_and_recog_new_device (struct subchannel*) ; 
 int sch_get_action (struct subchannel*) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_subchannel_sch_event(struct subchannel *sch, int process)
{
	unsigned long flags;
	struct ccw_device *cdev;
	struct ccw_dev_id dev_id;
	enum io_sch_action action;
	int rc = -EAGAIN;

	spin_lock_irqsave(sch->lock, flags);
	if (!device_is_registered(&sch->dev))
		goto out_unlock;
	if (work_pending(&sch->todo_work))
		goto out_unlock;
	cdev = sch_get_cdev(sch);
	if (cdev && work_pending(&cdev->private->todo_work))
		goto out_unlock;
	action = sch_get_action(sch);
	CIO_MSG_EVENT(2, "event: sch 0.%x.%04x, process=%d, action=%d\n",
		      sch->schid.ssid, sch->schid.sch_no, process,
		      action);
	/* Perform immediate actions while holding the lock. */
	switch (action) {
	case IO_SCH_REPROBE:
		/* Trigger device recognition. */
		ccw_device_trigger_reprobe(cdev);
		rc = 0;
		goto out_unlock;
	case IO_SCH_VERIFY:
		/* Trigger path verification. */
		io_subchannel_verify(sch);
		rc = 0;
		goto out_unlock;
	case IO_SCH_DISC:
		ccw_device_set_disconnected(cdev);
		rc = 0;
		goto out_unlock;
	case IO_SCH_ORPH_UNREG:
	case IO_SCH_ORPH_ATTACH:
		ccw_device_set_disconnected(cdev);
		break;
	case IO_SCH_UNREG_ATTACH:
	case IO_SCH_UNREG:
		if (!cdev)
			break;
		if (cdev->private->state == DEV_STATE_SENSE_ID) {
			/*
			 * Note: delayed work triggered by this event
			 * and repeated calls to sch_event are synchronized
			 * by the above check for work_pending(cdev).
			 */
			dev_fsm_event(cdev, DEV_EVENT_NOTOPER);
		} else
			ccw_device_set_notoper(cdev);
		break;
	case IO_SCH_NOP:
		rc = 0;
		goto out_unlock;
	default:
		break;
	}
	spin_unlock_irqrestore(sch->lock, flags);
	/* All other actions require process context. */
	if (!process)
		goto out;
	/* Handle attached ccw device. */
	switch (action) {
	case IO_SCH_ORPH_UNREG:
	case IO_SCH_ORPH_ATTACH:
		/* Move ccw device to orphanage. */
		rc = ccw_device_move_to_orph(cdev);
		if (rc)
			goto out;
		break;
	case IO_SCH_UNREG_ATTACH:
		/* Unregister ccw device. */
		if (!cdev->private->flags.resuming)
			ccw_device_unregister(cdev);
		break;
	default:
		break;
	}
	/* Handle subchannel. */
	switch (action) {
	case IO_SCH_ORPH_UNREG:
	case IO_SCH_UNREG:
		if (!cdev || !cdev->private->flags.resuming)
			css_sch_device_unregister(sch);
		break;
	case IO_SCH_ORPH_ATTACH:
	case IO_SCH_UNREG_ATTACH:
	case IO_SCH_ATTACH:
		dev_id.ssid = sch->schid.ssid;
		dev_id.devno = sch->schib.pmcw.dev;
		cdev = get_ccwdev_by_dev_id(&dev_id);
		if (!cdev) {
			sch_create_and_recog_new_device(sch);
			break;
		}
		rc = ccw_device_move_to_sch(cdev, sch);
		if (rc) {
			/* Release reference from get_ccwdev_by_dev_id() */
			put_device(&cdev->dev);
			goto out;
		}
		spin_lock_irqsave(sch->lock, flags);
		ccw_device_trigger_reprobe(cdev);
		spin_unlock_irqrestore(sch->lock, flags);
		/* Release reference from get_ccwdev_by_dev_id() */
		put_device(&cdev->dev);
		break;
	default:
		break;
	}
	return 0;

out_unlock:
	spin_unlock_irqrestore(sch->lock, flags);
out:
	return rc;
}