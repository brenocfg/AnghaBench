#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_driver {int /*<<< orphan*/  (* remove ) (struct device*) ;} ;
struct device {TYPE_3__* bus; TYPE_1__* p; struct device_driver* driver; } ;
struct TYPE_6__ {TYPE_2__* p; int /*<<< orphan*/  (* remove ) (struct device*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  bus_notifier; } ;
struct TYPE_4__ {int /*<<< orphan*/  knode_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_NOTIFY_UNBIND_DRIVER ; 
 int /*<<< orphan*/  BUS_NOTIFY_UNBOUND_DRIVER ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  devres_release_all (struct device*) ; 
 int /*<<< orphan*/  driver_sysfs_remove (struct device*) ; 
 int /*<<< orphan*/  klist_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_barrier (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 int /*<<< orphan*/  stub2 (struct device*) ; 

__attribute__((used)) static void __device_release_driver(struct device *dev)
{
	struct device_driver *drv;

	drv = dev->driver;
	if (drv) {
		pm_runtime_get_noresume(dev);
		pm_runtime_barrier(dev);

		driver_sysfs_remove(dev);

		if (dev->bus)
			blocking_notifier_call_chain(&dev->bus->p->bus_notifier,
						     BUS_NOTIFY_UNBIND_DRIVER,
						     dev);

		if (dev->bus && dev->bus->remove)
			dev->bus->remove(dev);
		else if (drv->remove)
			drv->remove(dev);
		devres_release_all(dev);
		dev->driver = NULL;
		klist_remove(&dev->p->knode_driver);
		if (dev->bus)
			blocking_notifier_call_chain(&dev->bus->p->bus_notifier,
						     BUS_NOTIFY_UNBOUND_DRIVER,
						     dev);

		pm_runtime_put_sync(dev);
	}
}