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
struct device {int dummy; } ;
struct ccw_driver {int /*<<< orphan*/  (* remove ) (struct ccw_device*) ;} ;
struct ccw_device {struct ccw_driver* drv; int /*<<< orphan*/  dev; TYPE_2__* private; int /*<<< orphan*/  ccwlock; scalar_t__ online; } ;
struct TYPE_3__ {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {TYPE_1__ dev_id; int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ccw_device_offline (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_fsm_final_state (struct ccw_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ccw_device_remove (struct device *dev)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct ccw_driver *cdrv = cdev->drv;
	int ret;

	if (cdrv->remove)
		cdrv->remove(cdev);
	if (cdev->online) {
		cdev->online = 0;
		spin_lock_irq(cdev->ccwlock);
		ret = ccw_device_offline(cdev);
		spin_unlock_irq(cdev->ccwlock);
		if (ret == 0)
			wait_event(cdev->private->wait_q,
				   dev_fsm_final_state(cdev));
		else
			CIO_MSG_EVENT(0, "ccw_device_offline returned %d, "
				      "device 0.%x.%04x\n",
				      ret, cdev->private->dev_id.ssid,
				      cdev->private->dev_id.devno);
		/* Give up reference obtained in ccw_device_set_online(). */
		put_device(&cdev->dev);
	}
	ccw_device_set_timeout(cdev, 0);
	cdev->drv = NULL;
	return 0;
}