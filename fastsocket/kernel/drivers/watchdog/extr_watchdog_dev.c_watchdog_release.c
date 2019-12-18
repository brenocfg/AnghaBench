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
struct watchdog_device {TYPE_2__* ops; int /*<<< orphan*/  status; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__* info; } ;
struct inode {int dummy; } ;
struct file {struct watchdog_device* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* unref ) (struct watchdog_device*) ;int /*<<< orphan*/  owner; } ;
struct TYPE_3__ {int options; } ;

/* Variables and functions */
 int EBUSY ; 
 int WDIOF_MAGICCLOSE ; 
 int /*<<< orphan*/  WDOG_ALLOW_RELEASE ; 
 int /*<<< orphan*/  WDOG_DEV_OPEN ; 
 int /*<<< orphan*/  WDOG_UNREGISTERED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct watchdog_device*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_ping (struct watchdog_device*) ; 
 int watchdog_stop (struct watchdog_device*) ; 

__attribute__((used)) static int watchdog_release(struct inode *inode, struct file *file)
{
	struct watchdog_device *wdd = file->private_data;
	int err = -EBUSY;

	/*
	 * We only stop the watchdog if we received the magic character
	 * or if WDIOF_MAGICCLOSE is not set. If nowayout was set then
	 * watchdog_stop will fail.
	 */
	if (test_and_clear_bit(WDOG_ALLOW_RELEASE, &wdd->status) ||
	    !(wdd->info->options & WDIOF_MAGICCLOSE))
		err = watchdog_stop(wdd);

	/* If the watchdog was not stopped, send a keepalive ping */
	if (err < 0) {
		mutex_lock(&wdd->lock);
		if (!test_bit(WDOG_UNREGISTERED, &wdd->status))
			dev_crit(wdd->dev, "watchdog did not stop!\n");
		mutex_unlock(&wdd->lock);
		watchdog_ping(wdd);
	}

	/* Allow the owner module to be unloaded again */
	module_put(wdd->ops->owner);

	/* make sure that /dev/watchdog can be re-opened */
	clear_bit(WDOG_DEV_OPEN, &wdd->status);

	/* Note wdd may be gone after this, do not use after this! */
	if (wdd->ops->unref)
		wdd->ops->unref(wdd);

	return 0;
}