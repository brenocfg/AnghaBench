#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct watchdog_device {scalar_t__ id; int /*<<< orphan*/  cdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDOG_UNREGISTERED ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * old_wdd ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_miscdev ; 

int watchdog_dev_unregister(struct watchdog_device *watchdog)
{
	mutex_lock(&watchdog->lock);
	set_bit(WDOG_UNREGISTERED, &watchdog->status);
	mutex_unlock(&watchdog->lock);

	cdev_del(&watchdog->cdev);
	if (watchdog->id == 0) {
		misc_deregister(&watchdog_miscdev);
		old_wdd = NULL;
	}
	return 0;
}