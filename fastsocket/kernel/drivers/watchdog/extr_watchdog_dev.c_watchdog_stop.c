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
struct watchdog_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  status; TYPE_1__* ops; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* stop ) (struct watchdog_device*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  WDOG_ACTIVE ; 
 int /*<<< orphan*/  WDOG_NO_WAY_OUT ; 
 int /*<<< orphan*/  WDOG_UNREGISTERED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct watchdog_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_active (struct watchdog_device*) ; 

__attribute__((used)) static int watchdog_stop(struct watchdog_device *wddev)
{
	int err = 0;

	mutex_lock(&wddev->lock);

	if (test_bit(WDOG_UNREGISTERED, &wddev->status)) {
		err = -ENODEV;
		goto out_stop;
	}

	if (!watchdog_active(wddev))
		goto out_stop;

	if (test_bit(WDOG_NO_WAY_OUT, &wddev->status)) {
		dev_info(wddev->dev, "nowayout prevents watchdog being stopped!\n");
		err = -EBUSY;
		goto out_stop;
	}

	err = wddev->ops->stop(wddev);
	if (err == 0)
		clear_bit(WDOG_ACTIVE, &wddev->status);

out_stop:
	mutex_unlock(&wddev->lock);
	return err;
}