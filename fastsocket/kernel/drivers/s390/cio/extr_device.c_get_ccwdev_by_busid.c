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
struct device_driver {int dummy; } ;
struct device {int dummy; } ;
struct ccw_driver {int /*<<< orphan*/  driver; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ccwdev_check_busid ; 
 struct device* driver_find_device (struct device_driver*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 struct device_driver* get_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_driver (struct device_driver*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

struct ccw_device *get_ccwdev_by_busid(struct ccw_driver *cdrv,
				       const char *bus_id)
{
	struct device *dev;
	struct device_driver *drv;

	drv = get_driver(&cdrv->driver);
	if (!drv)
		return NULL;

	dev = driver_find_device(drv, NULL, (void *)bus_id,
				 __ccwdev_check_busid);
	put_driver(drv);

	return dev ? to_ccwdev(dev) : NULL;
}