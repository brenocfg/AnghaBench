#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct subchannel {int /*<<< orphan*/  lock; TYPE_6__ schid; int /*<<< orphan*/  private; TYPE_5__ dev; } ;
struct io_subchannel_private {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  groups; } ;
struct ccw_device {TYPE_3__ dev; TYPE_2__* private; } ;
struct TYPE_8__ {int initialized; } ;
struct TYPE_9__ {scalar_t__ state; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DEV_STATE_BOXED ; 
 scalar_t__ DEV_STATE_NOT_OPER ; 
 scalar_t__ DEV_STATE_OFFLINE ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  SCH_TODO_UNREG ; 
 int /*<<< orphan*/  ccw_device_register (struct ccw_device*) ; 
 int /*<<< orphan*/  ccwdev_attr_groups ; 
 int cio_commit_config (struct subchannel*) ; 
 scalar_t__ cio_is_console (TYPE_6__) ; 
 int /*<<< orphan*/  css_sched_sch_todo (struct subchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_schedule_eval (TYPE_6__) ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_3__*) ; 
 int /*<<< orphan*/  get_device (TYPE_3__*) ; 
 int /*<<< orphan*/  io_subchannel_attr_group ; 
 int /*<<< orphan*/  io_subchannel_init_fields (struct subchannel*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_subchannel_probe(struct subchannel *sch)
{
	struct ccw_device *cdev;
	int rc;

	if (cio_is_console(sch->schid)) {
		rc = sysfs_create_group(&sch->dev.kobj,
					&io_subchannel_attr_group);
		if (rc)
			CIO_MSG_EVENT(0, "Failed to create io subchannel "
				      "attributes for subchannel "
				      "0.%x.%04x (rc=%d)\n",
				      sch->schid.ssid, sch->schid.sch_no, rc);
		/*
		 * The console subchannel already has an associated ccw_device.
		 * Throw the delayed uevent for the subchannel, register
		 * the ccw_device and exit.
		 */
		dev_set_uevent_suppress(&sch->dev, 0);
		kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
		cdev = sch_get_cdev(sch);
		cdev->dev.groups = ccwdev_attr_groups;
		device_initialize(&cdev->dev);
		cdev->private->flags.initialized = 1;
		ccw_device_register(cdev);
		/*
		 * Check if the device is already online. If it is
		 * the reference count needs to be corrected since we
		 * didn't obtain a reference in ccw_device_set_online.
		 */
		if (cdev->private->state != DEV_STATE_NOT_OPER &&
		    cdev->private->state != DEV_STATE_OFFLINE &&
		    cdev->private->state != DEV_STATE_BOXED)
			get_device(&cdev->dev);
		return 0;
	}
	io_subchannel_init_fields(sch);
	rc = cio_commit_config(sch);
	if (rc)
		goto out_schedule;
	rc = sysfs_create_group(&sch->dev.kobj,
				&io_subchannel_attr_group);
	if (rc)
		goto out_schedule;
	/* Allocate I/O subchannel private data. */
	sch->private = kzalloc(sizeof(struct io_subchannel_private),
			       GFP_KERNEL | GFP_DMA);
	if (!sch->private)
		goto out_schedule;
	css_schedule_eval(sch->schid);
	return 0;

out_schedule:
	spin_lock_irq(sch->lock);
	css_sched_sch_todo(sch, SCH_TODO_UNREG);
	spin_unlock_irq(sch->lock);
	return 0;
}