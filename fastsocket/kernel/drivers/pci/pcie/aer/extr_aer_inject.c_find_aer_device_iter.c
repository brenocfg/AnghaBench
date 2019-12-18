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
struct pcie_device {int service; } ;
struct device {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int PCIE_PORT_SERVICE_AER ; 
 int /*<<< orphan*/  pcie_port_bus_type ; 
 struct pcie_device* to_pcie_device (struct device*) ; 

__attribute__((used)) static int find_aer_device_iter(struct device *device, void *data)
{
	struct pcie_device **result = data;
	struct pcie_device *pcie_dev;

	if (device->bus == &pcie_port_bus_type) {
		pcie_dev = to_pcie_device(device);
		if (pcie_dev->service & PCIE_PORT_SERVICE_AER) {
			*result = pcie_dev;
			return 1;
		}
	}
	return 0;
}