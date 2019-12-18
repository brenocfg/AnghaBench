#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_driver {TYPE_2__* bus; TYPE_1__* p; int /*<<< orphan*/  name; int /*<<< orphan*/  suppress_bind_attrs; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  knode_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_put (TYPE_2__*) ; 
 int /*<<< orphan*/  driver_attr_uevent ; 
 int /*<<< orphan*/  driver_detach (struct device_driver*) ; 
 int /*<<< orphan*/  driver_remove_attrs (TYPE_2__*,struct device_driver*) ; 
 int /*<<< orphan*/  driver_remove_file (struct device_driver*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  klist_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_remove_driver (struct device_driver*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_bind_files (struct device_driver*) ; 

void bus_remove_driver(struct device_driver *drv)
{
	if (!drv->bus)
		return;

	if (!drv->suppress_bind_attrs)
		remove_bind_files(drv);
	driver_remove_attrs(drv->bus, drv);
	driver_remove_file(drv, &driver_attr_uevent);
	klist_remove(&drv->p->knode_bus);
	pr_debug("bus: '%s': remove driver %s\n", drv->bus->name, drv->name);
	driver_detach(drv);
	module_remove_driver(drv);
	kobject_put(&drv->p->kobj);
	bus_put(drv->bus);
}