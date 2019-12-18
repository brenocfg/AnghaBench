#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * dma_ops; } ;
struct TYPE_4__ {TYPE_1__ archdata; int /*<<< orphan*/ * bus; } ;
struct of_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ibmebus_bus_device ; 
 int /*<<< orphan*/  ibmebus_bus_type ; 
 int /*<<< orphan*/  ibmebus_dma_ops ; 
 struct of_device* of_device_alloc (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_free (struct of_device*) ; 
 int of_device_register (struct of_device*) ; 

__attribute__((used)) static int ibmebus_create_device(struct device_node *dn)
{
	struct of_device *dev;
	int ret;

	dev = of_device_alloc(dn, NULL, &ibmebus_bus_device);
	if (!dev)
		return -ENOMEM;

	dev->dev.bus = &ibmebus_bus_type;
	dev->dev.archdata.dma_ops = &ibmebus_dma_ops;

	ret = of_device_register(dev);
	if (ret) {
		of_device_free(dev);
		return ret;
	}

	return 0;
}