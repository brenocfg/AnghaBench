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
struct pci_dev {int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ acpi_pci_can_wakeup (struct pci_dev*) ; 
 int /*<<< orphan*/  acpi_pci_propagate_wakeup_enable (int /*<<< orphan*/ ,int) ; 
 int acpi_pm_device_sleep_wake (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 

__attribute__((used)) static int acpi_pci_sleep_wake(struct pci_dev *dev, bool enable)
{
	if (acpi_pci_can_wakeup(dev))
		return acpi_pm_device_sleep_wake(&dev->dev, enable);

	if (!pci_is_pcie(dev))
		acpi_pci_propagate_wakeup_enable(dev->bus, enable);

	return 0;
}