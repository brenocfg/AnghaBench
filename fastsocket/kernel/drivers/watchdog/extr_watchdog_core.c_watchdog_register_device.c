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
struct TYPE_4__ {int dev; } ;
struct watchdog_device {scalar_t__ min_timeout; scalar_t__ max_timeout; int id; int /*<<< orphan*/  dev; int /*<<< orphan*/  parent; TYPE_2__ cdev; int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/ * info; } ;
struct TYPE_3__ {int /*<<< orphan*/ * stop; int /*<<< orphan*/ * start; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_DOGS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*,int) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  watchdog_class ; 
 int watchdog_dev_register (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_dev_unregister (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_ida ; 

int watchdog_register_device(struct watchdog_device *wdd)
{
	int ret, id, devno;

	if (wdd == NULL || wdd->info == NULL || wdd->ops == NULL)
		return -EINVAL;

	/* Mandatory operations need to be supported */
	if (wdd->ops->start == NULL || wdd->ops->stop == NULL)
		return -EINVAL;

	/*
	 * Check that we have valid min and max timeout values, if
	 * not reset them both to 0 (=not used or unknown)
	 */
	if (wdd->min_timeout > wdd->max_timeout) {
		pr_info("Invalid min and max timeout values, resetting to 0!\n");
		wdd->min_timeout = 0;
		wdd->max_timeout = 0;
	}

	/*
	 * Note: now that all watchdog_device data has been verified, we
	 * will not check this anymore in other functions. If data gets
	 * corrupted in a later stage then we expect a kernel panic!
	 */

	mutex_init(&wdd->lock);
	id = ida_simple_get(&watchdog_ida, 0, MAX_DOGS, GFP_KERNEL);
	if (id < 0)
		return id;
	wdd->id = id;

	ret = watchdog_dev_register(wdd);
	if (ret) {
		ida_simple_remove(&watchdog_ida, id);
		if (!(id == 0 && ret == -EBUSY))
			return ret;

		/* Retry in case a legacy watchdog module exists */
		id = ida_simple_get(&watchdog_ida, 1, MAX_DOGS, GFP_KERNEL);
		if (id < 0)
			return id;
		wdd->id = id;

		ret = watchdog_dev_register(wdd);
		if (ret) {
			ida_simple_remove(&watchdog_ida, id);
			return ret;
		}
	}

	devno = wdd->cdev.dev;
	wdd->dev = device_create(watchdog_class, wdd->parent, devno,
					NULL, "watchdog%d", wdd->id);
	if (IS_ERR(wdd->dev)) {
		watchdog_dev_unregister(wdd);
		ida_simple_remove(&watchdog_ida, id);
		ret = PTR_ERR(wdd->dev);
		return ret;
	}

	return 0;
}