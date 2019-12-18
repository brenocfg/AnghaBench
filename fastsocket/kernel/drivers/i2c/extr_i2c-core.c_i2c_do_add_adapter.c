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
struct i2c_driver {int /*<<< orphan*/  (* attach_adapter ) (struct i2c_adapter*) ;} ;
struct i2c_adapter {int dummy; } ;
struct device_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_detect (struct i2c_adapter*,struct i2c_driver*) ; 
 int /*<<< orphan*/  stub1 (struct i2c_adapter*) ; 
 struct i2c_driver* to_i2c_driver (struct device_driver*) ; 

__attribute__((used)) static int i2c_do_add_adapter(struct device_driver *d, void *data)
{
	struct i2c_driver *driver = to_i2c_driver(d);
	struct i2c_adapter *adap = data;

	/* Detect supported devices on that bus, and instantiate them */
	i2c_detect(adap, driver);

	/* Let legacy drivers scan this bus for matching devices */
	if (driver->attach_adapter) {
		/* We ignore the return code; if it fails, too bad */
		driver->attach_adapter(adap);
	}
	return 0;
}