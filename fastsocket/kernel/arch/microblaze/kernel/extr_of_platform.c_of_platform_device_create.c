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
struct TYPE_2__ {int /*<<< orphan*/ * bus; } ;
struct of_device {int dma_mask; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct of_device* of_device_alloc (struct device_node*,char const*,struct device*) ; 
 int /*<<< orphan*/  of_device_free (struct of_device*) ; 
 scalar_t__ of_device_register (struct of_device*) ; 
 int /*<<< orphan*/  of_platform_bus_type ; 

struct of_device *of_platform_device_create(struct device_node *np,
					    const char *bus_id,
					    struct device *parent)
{
	struct of_device *dev;

	dev = of_device_alloc(np, bus_id, parent);
	if (!dev)
		return NULL;

	dev->dma_mask = 0xffffffffUL;
	dev->dev.bus = &of_platform_bus_type;

	/* We do not fill the DMA ops for platform devices by default.
	 * This is currently the responsibility of the platform code
	 * to do such, possibly using a device notifier
	 */

	if (of_device_register(dev) != 0) {
		of_device_free(dev);
		return NULL;
	}

	return dev;
}