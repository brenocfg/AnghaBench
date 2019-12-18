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
typedef  int /*<<< orphan*/  pci_power_t ;

/* Variables and functions */
#define  ACPI_STATE_D0 131 
#define  ACPI_STATE_D1 130 
#define  ACPI_STATE_D2 129 
#define  ACPI_STATE_D3 128 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_D1 ; 
 int /*<<< orphan*/  PCI_D2 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  PCI_POWER_ERROR ; 
 int acpi_pm_device_sleep_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pci_power_t acpi_pci_choose_state(struct pci_dev *pdev)
{
	int acpi_state;

	acpi_state = acpi_pm_device_sleep_state(&pdev->dev, NULL);
	if (acpi_state < 0)
		return PCI_POWER_ERROR;

	switch (acpi_state) {
	case ACPI_STATE_D0:
		return PCI_D0;
	case ACPI_STATE_D1:
		return PCI_D1;
	case ACPI_STATE_D2:
		return PCI_D2;
	case ACPI_STATE_D3:
		return PCI_D3hot;
	}
	return PCI_POWER_ERROR;
}