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
struct watchdog_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  status; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* start ) (struct watchdog_device*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  WDOG_ACTIVE ; 
 int /*<<< orphan*/  WDOG_UNREGISTERED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct watchdog_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ watchdog_active (struct watchdog_device*) ; 

__attribute__((used)) static int watchdog_start(struct watchdog_device *wddev)
{
	int err = 0;

	mutex_lock(&wddev->lock);

	if (test_bit(WDOG_UNREGISTERED, &wddev->status)) {
		err = -ENODEV;
		goto out_start;
	}

	if (watchdog_active(wddev))
		goto out_start;

	err = wddev->ops->start(wddev);
	if (err == 0)
		set_bit(WDOG_ACTIVE, &wddev->status);

out_start:
	mutex_unlock(&wddev->lock);
	return err;
}