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
struct module {int dummy; } ;
struct device_driver {char* name; struct module* owner; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; int /*<<< orphan*/ * bus; } ;
struct ap_driver {struct device_driver driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_bus_type ; 
 int /*<<< orphan*/  ap_device_probe ; 
 int /*<<< orphan*/  ap_device_remove ; 
 int driver_register (struct device_driver*) ; 

int ap_driver_register(struct ap_driver *ap_drv, struct module *owner,
		       char *name)
{
	struct device_driver *drv = &ap_drv->driver;

	drv->bus = &ap_bus_type;
	drv->probe = ap_device_probe;
	drv->remove = ap_device_remove;
	drv->owner = owner;
	drv->name = name;
	return driver_register(drv);
}