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
struct device {int /*<<< orphan*/  sem; int /*<<< orphan*/  bus; int /*<<< orphan*/ * driver; TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  knode_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  __device_attach ; 
 int bus_for_each_drv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ ) ; 
 int device_bind_driver (struct device*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 scalar_t__ klist_node_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int device_attach(struct device *dev)
{
	int ret = 0;

	down(&dev->sem);
	if (dev->driver) {
		if (klist_node_attached(&dev->p->knode_driver)) {
			ret = 1;
			goto out_unlock;
		}
		ret = device_bind_driver(dev);
		if (ret == 0)
			ret = 1;
		else {
			dev->driver = NULL;
			ret = 0;
		}
	} else {
		pm_runtime_get_noresume(dev);
		ret = bus_for_each_drv(dev->bus, NULL, dev, __device_attach);
		pm_runtime_put_sync(dev);
	}
out_unlock:
	up(&dev->sem);
	return ret;
}