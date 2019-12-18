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
struct TYPE_2__ {struct bus_type* bus; scalar_t__ owner; scalar_t__ name; } ;
struct of_platform_driver {TYPE_1__ driver; scalar_t__ owner; scalar_t__ name; } ;
struct bus_type {int dummy; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 

int of_register_driver(struct of_platform_driver *drv, struct bus_type *bus)
{
	/* initialize common driver fields */
	if (!drv->driver.name)
		drv->driver.name = drv->name;
	if (!drv->driver.owner)
		drv->driver.owner = drv->owner;
	drv->driver.bus = bus;

	/* register with core */
	return driver_register(&drv->driver);
}