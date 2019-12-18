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
struct pci_dev {struct pci_bus* bus; } ;
struct pci_bus {struct pci_bus* parent; } ;
struct hotplug_params {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ acpi_is_root_bridge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acpi_pci_get_bridge_handle (struct pci_bus*) ; 
 int /*<<< orphan*/  acpi_run_hpp (int /*<<< orphan*/ *,struct hotplug_params*) ; 
 int /*<<< orphan*/  acpi_run_hpx (int /*<<< orphan*/ *,struct hotplug_params*) ; 

int pci_get_hp_params(struct pci_dev *dev, struct hotplug_params *hpp)
{
	acpi_status status;
	acpi_handle handle, phandle;
	struct pci_bus *pbus;

	handle = NULL;
	for (pbus = dev->bus; pbus; pbus = pbus->parent) {
		handle = acpi_pci_get_bridge_handle(pbus);
		if (handle)
			break;
	}

	/*
	 * _HPP settings apply to all child buses, until another _HPP is
	 * encountered. If we don't find an _HPP for the input pci dev,
	 * look for it in the parent device scope since that would apply to
	 * this pci dev.
	 */
	while (handle) {
		status = acpi_run_hpx(handle, hpp);
		if (ACPI_SUCCESS(status))
			return 0;
		status = acpi_run_hpp(handle, hpp);
		if (ACPI_SUCCESS(status))
			return 0;
		if (acpi_is_root_bridge(handle))
			break;
		status = acpi_get_parent(handle, &phandle);
		if (ACPI_FAILURE(status))
			break;
		handle = phandle;
	}
	return -ENODEV;
}