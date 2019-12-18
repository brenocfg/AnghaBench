#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; } ;
struct lm_device {TYPE_1__ resource; TYPE_3__ dev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int dev_set_name (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  iomem_resource ; 
 int /*<<< orphan*/  lm_bustype ; 
 int /*<<< orphan*/  lm_device_release ; 
 int /*<<< orphan*/  release_resource (TYPE_1__*) ; 
 int request_resource (int /*<<< orphan*/ *,TYPE_1__*) ; 

int lm_device_register(struct lm_device *dev)
{
	int ret;

	dev->dev.release = lm_device_release;
	dev->dev.bus = &lm_bustype;

	ret = dev_set_name(&dev->dev, "lm%d", dev->id);
	if (ret)
		return ret;
	dev->resource.name = dev_name(&dev->dev);

	ret = request_resource(&iomem_resource, &dev->resource);
	if (ret == 0) {
		ret = device_register(&dev->dev);
		if (ret)
			release_resource(&dev->resource);
	}
	return ret;
}