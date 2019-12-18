#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_4__* bus; TYPE_3__* p; int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; TYPE_2__* p; } ;
struct TYPE_8__ {int /*<<< orphan*/  knode_bus; } ;
struct TYPE_7__ {TYPE_1__* devices_kset; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_put (TYPE_4__*) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  device_release_driver (struct device*) ; 
 int /*<<< orphan*/  device_remove_attrs (TYPE_4__*,struct device*) ; 
 int /*<<< orphan*/  klist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ klist_node_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  remove_deprecated_bus_links (struct device*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void bus_remove_device(struct device *dev)
{
	if (dev->bus) {
		sysfs_remove_link(&dev->kobj, "subsystem");
		remove_deprecated_bus_links(dev);
		sysfs_remove_link(&dev->bus->p->devices_kset->kobj,
				  dev_name(dev));
		device_remove_attrs(dev->bus, dev);
		if (klist_node_attached(&dev->p->knode_bus))
			klist_del(&dev->p->knode_bus);

		pr_debug("bus: '%s': remove device %s\n",
			 dev->bus->name, dev_name(dev));
		device_release_driver(dev);
		bus_put(dev->bus);
	}
}