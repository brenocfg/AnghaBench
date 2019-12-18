#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  pcie_port_bus_type ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static int remove_iter(struct device *dev, void *data)
{
	if (dev->bus == &pcie_port_bus_type) {
		put_device(dev);
		device_unregister(dev);
	}
	return 0;
}