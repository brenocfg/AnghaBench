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
struct pcie_port_service_driver {scalar_t__ service; } ;
struct device {scalar_t__ driver; int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 scalar_t__ PCIE_PORT_SERVICE_AER ; 
 int /*<<< orphan*/  pcie_port_bus_type ; 
 struct pcie_port_service_driver* to_service_driver (scalar_t__) ; 

__attribute__((used)) static int find_aer_service_iter(struct device *device, void *data)
{
	struct pcie_port_service_driver *service_driver, **drv;

	drv = (struct pcie_port_service_driver **) data;

	if (device->bus == &pcie_port_bus_type && device->driver) {
		service_driver = to_service_driver(device->driver);
		if (service_driver->service == PCIE_PORT_SERVICE_AER) {
			*drv = service_driver;
			return 1;
		}
	}

	return 0;
}