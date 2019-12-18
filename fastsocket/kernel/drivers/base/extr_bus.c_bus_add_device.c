#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_6__* bus; int /*<<< orphan*/  kobj; TYPE_3__* p; } ;
struct bus_type {TYPE_5__* p; int /*<<< orphan*/  name; } ;
struct TYPE_13__ {TYPE_2__* p; } ;
struct TYPE_12__ {TYPE_4__* devices_kset; int /*<<< orphan*/  klist_devices; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_10__ {int /*<<< orphan*/  knode_bus; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {TYPE_1__ subsys; } ;

/* Variables and functions */
 struct bus_type* bus_get (TYPE_6__*) ; 
 int /*<<< orphan*/  bus_put (TYPE_6__*) ; 
 char* dev_name (struct device*) ; 
 int device_add_attrs (struct bus_type*,struct device*) ; 
 int /*<<< orphan*/  device_remove_attrs (struct bus_type*,struct device*) ; 
 int /*<<< orphan*/  klist_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int make_deprecated_bus_links (struct device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

int bus_add_device(struct device *dev)
{
	struct bus_type *bus = bus_get(dev->bus);
	int error = 0;

	if (bus) {
		pr_debug("bus: '%s': add device %s\n", bus->name, dev_name(dev));
		error = device_add_attrs(bus, dev);
		if (error)
			goto out_put;
		error = sysfs_create_link(&bus->p->devices_kset->kobj,
						&dev->kobj, dev_name(dev));
		if (error)
			goto out_id;
		error = sysfs_create_link(&dev->kobj,
				&dev->bus->p->subsys.kobj, "subsystem");
		if (error)
			goto out_subsys;
		error = make_deprecated_bus_links(dev);
		if (error)
			goto out_deprecated;
		klist_add_tail(&dev->p->knode_bus, &bus->p->klist_devices);
	}
	return 0;

out_deprecated:
	sysfs_remove_link(&dev->kobj, "subsystem");
out_subsys:
	sysfs_remove_link(&bus->p->devices_kset->kobj, dev_name(dev));
out_id:
	device_remove_attrs(bus, dev);
out_put:
	bus_put(dev->bus);
	return error;
}