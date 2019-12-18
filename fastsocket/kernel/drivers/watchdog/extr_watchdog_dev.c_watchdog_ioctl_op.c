#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int (* ioctl ) (struct watchdog_device*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  WDOG_UNREGISTERED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct watchdog_device*,unsigned int,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int watchdog_ioctl_op(struct watchdog_device *wddev, unsigned int cmd,
							unsigned long arg)
{
	int err;

	if (!wddev->ops->ioctl)
		return -ENOIOCTLCMD;

	mutex_lock(&wddev->lock);

	if (test_bit(WDOG_UNREGISTERED, &wddev->status)) {
		err = -ENODEV;
		goto out_ioctl;
	}

	err = wddev->ops->ioctl(wddev, cmd, arg);

out_ioctl:
	mutex_unlock(&wddev->lock);
	return err;
}