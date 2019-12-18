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
struct bus_type {int /*<<< orphan*/ * drv_attrs; } ;

/* Variables and functions */
 scalar_t__ attr_name (int /*<<< orphan*/ ) ; 
 int driver_create_file (struct device_driver*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_remove_file (struct device_driver*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int driver_add_attrs(struct bus_type *bus, struct device_driver *drv)
{
	int error = 0;
	int i;

	if (bus->drv_attrs) {
		for (i = 0; attr_name(bus->drv_attrs[i]); i++) {
			error = driver_create_file(drv, &bus->drv_attrs[i]);
			if (error)
				goto err;
		}
	}
done:
	return error;
err:
	while (--i >= 0)
		driver_remove_file(drv, &bus->drv_attrs[i]);
	goto done;
}