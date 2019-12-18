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
struct ccw_device {TYPE_1__* drv; TYPE_2__* private; int /*<<< orphan*/  ccwlock; } ;
struct TYPE_6__ {int /*<<< orphan*/  recog_done; } ;
struct TYPE_5__ {scalar_t__ state; TYPE_3__ flags; int /*<<< orphan*/  wait_q; } ;
struct TYPE_4__ {scalar_t__ set_online; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_BOXED ; 
 scalar_t__ DEV_STATE_OFFLINE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  ccw_device_recognition (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_set_online (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int online_store_recog_and_online(struct ccw_device *cdev)
{
	/* Do device recognition, if needed. */
	if (cdev->private->state == DEV_STATE_BOXED) {
		spin_lock_irq(cdev->ccwlock);
		ccw_device_recognition(cdev);
		spin_unlock_irq(cdev->ccwlock);
		wait_event(cdev->private->wait_q,
			   cdev->private->flags.recog_done);
		if (cdev->private->state != DEV_STATE_OFFLINE)
			/* recognition failed */
			return -EAGAIN;
	}
	if (cdev->drv && cdev->drv->set_online)
		ccw_device_set_online(cdev);
	return 0;
}