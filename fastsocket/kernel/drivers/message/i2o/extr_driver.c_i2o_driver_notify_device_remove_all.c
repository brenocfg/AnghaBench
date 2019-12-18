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
struct i2o_driver {int dummy; } ;
struct i2o_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2o_driver_notify_device_remove (struct i2o_driver*,struct i2o_device*) ; 
 struct i2o_driver** i2o_drivers ; 
 int i2o_max_drivers ; 

void i2o_driver_notify_device_remove_all(struct i2o_device *i2o_dev)
{
	int i;
	struct i2o_driver *drv;

	for (i = 0; i < i2o_max_drivers; i++) {
		drv = i2o_drivers[i];

		if (drv)
			i2o_driver_notify_device_remove(drv, i2o_dev);
	}
}