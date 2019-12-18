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
struct TYPE_5__ {scalar_t__ pool; } ;
struct TYPE_4__ {scalar_t__ pool; } ;
struct dmabounce_device_info {scalar_t__ attr_res; TYPE_2__ large; TYPE_1__ small; int /*<<< orphan*/  safe_buffers; } ;
struct TYPE_6__ {struct dmabounce_device_info* dmabounce; } ;
struct device {TYPE_3__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  dev_attr_dmabounce_stats ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dmabounce_device_info*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void dmabounce_unregister_dev(struct device *dev)
{
	struct dmabounce_device_info *device_info = dev->archdata.dmabounce;

	dev->archdata.dmabounce = NULL;

	if (!device_info) {
		dev_warn(dev,
			 "Never registered with dmabounce but attempting"
			 "to unregister!\n");
		return;
	}

	if (!list_empty(&device_info->safe_buffers)) {
		dev_err(dev,
			"Removing from dmabounce with pending buffers!\n");
		BUG();
	}

	if (device_info->small.pool)
		dma_pool_destroy(device_info->small.pool);
	if (device_info->large.pool)
		dma_pool_destroy(device_info->large.pool);

#ifdef STATS
	if (device_info->attr_res == 0)
		device_remove_file(dev, &dev_attr_dmabounce_stats);
#endif

	kfree(device_info);

	dev_info(dev, "dmabounce: device unregistered\n");
}