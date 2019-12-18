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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct pci_bus {int /*<<< orphan*/ * bridge; struct pci_bus* parent; struct pci_dev* self; } ;

/* Variables and functions */
 int acpi_pm_device_sleep_wake (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 

__attribute__((used)) static void acpi_pci_propagate_wakeup_enable(struct pci_bus *bus, bool enable)
{
	while (bus->parent) {
		struct pci_dev *bridge = bus->self;
		int ret;

		ret = acpi_pm_device_sleep_wake(&bridge->dev, enable);
		if (!ret || pci_is_pcie(bridge))
			return;
		bus = bus->parent;
	}

	/* We have reached the root bus. */
	if (bus->bridge)
		acpi_pm_device_sleep_wake(bus->bridge, enable);
}