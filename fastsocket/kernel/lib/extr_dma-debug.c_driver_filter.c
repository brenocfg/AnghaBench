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
struct device_driver {scalar_t__ name; } ;
struct device {struct device_driver* driver; } ;

/* Variables and functions */
 scalar_t__ NAME_MAX_LEN ; 
 struct device_driver* current_driver ; 
 int /*<<< orphan*/ * current_driver_name ; 
 int /*<<< orphan*/  driver_name_lock ; 
 struct device_driver* get_driver (struct device_driver*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  put_driver (struct device_driver*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool driver_filter(struct device *dev)
{
	struct device_driver *drv;
	unsigned long flags;
	bool ret;

	/* driver filter off */
	if (likely(!current_driver_name[0]))
		return true;

	/* driver filter on and initialized */
	if (current_driver && dev && dev->driver == current_driver)
		return true;

	/* driver filter on, but we can't filter on a NULL device... */
	if (!dev)
		return false;

	if (current_driver || !current_driver_name[0])
		return false;

	/* driver filter on but not yet initialized */
	drv = get_driver(dev->driver);
	if (!drv)
		return false;

	/* lock to protect against change of current_driver_name */
	read_lock_irqsave(&driver_name_lock, flags);

	ret = false;
	if (drv->name &&
	    strncmp(current_driver_name, drv->name, NAME_MAX_LEN - 1) == 0) {
		current_driver = drv;
		ret = true;
	}

	read_unlock_irqrestore(&driver_name_lock, flags);
	put_driver(drv);

	return ret;
}