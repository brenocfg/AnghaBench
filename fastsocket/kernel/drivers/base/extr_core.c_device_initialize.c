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
struct TYPE_2__ {int /*<<< orphan*/  kset; } ;
struct device {int /*<<< orphan*/  devres_head; int /*<<< orphan*/  devres_lock; int /*<<< orphan*/  sem; int /*<<< orphan*/  dma_pools; TYPE_1__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_ktype ; 
 int /*<<< orphan*/  device_pm_init (struct device*) ; 
 int /*<<< orphan*/  devices_kset ; 
 int /*<<< orphan*/  init_MUTEX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dev_node (struct device*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void device_initialize(struct device *dev)
{
	dev->kobj.kset = devices_kset;
	kobject_init(&dev->kobj, &device_ktype);
	INIT_LIST_HEAD(&dev->dma_pools);
	init_MUTEX(&dev->sem);
	spin_lock_init(&dev->devres_lock);
	INIT_LIST_HEAD(&dev->devres_head);
	device_init_wakeup(dev, 0);
	device_pm_init(dev);
	set_dev_node(dev, -1);
}