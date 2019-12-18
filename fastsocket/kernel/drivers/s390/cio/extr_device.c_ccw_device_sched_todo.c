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
struct ccw_device {int /*<<< orphan*/  dev; TYPE_2__* private; } ;
typedef  enum cdev_todo { ____Placeholder_cdev_todo } cdev_todo ;
struct TYPE_3__ {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {int todo; int /*<<< orphan*/  todo_work; TYPE_1__ dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cio_work_q ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ccw_device_sched_todo(struct ccw_device *cdev, enum cdev_todo todo)
{
	CIO_MSG_EVENT(4, "cdev_todo: sched cdev=0.%x.%04x todo=%d\n",
		      cdev->private->dev_id.ssid, cdev->private->dev_id.devno,
		      todo);
	if (cdev->private->todo >= todo)
		return;
	cdev->private->todo = todo;
	/* Get workqueue ref. */
	if (!get_device(&cdev->dev))
		return;
	if (!queue_work(cio_work_q, &cdev->private->todo_work)) {
		/* Already queued, release workqueue ref. */
		put_device(&cdev->dev);
	}
}