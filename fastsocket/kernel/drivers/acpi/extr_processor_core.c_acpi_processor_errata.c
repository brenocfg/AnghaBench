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
struct pci_dev {int dummy; } ;
struct acpi_processor {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCI_ANY_ID ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_82371AB_3 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int acpi_processor_errata_piix4 (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_subsys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_processor_errata(struct acpi_processor *pr)
{
	int result = 0;
	struct pci_dev *dev = NULL;


	if (!pr)
		return -EINVAL;

	/*
	 * PIIX4
	 */
	dev = pci_get_subsys(PCI_VENDOR_ID_INTEL,
			     PCI_DEVICE_ID_INTEL_82371AB_3, PCI_ANY_ID,
			     PCI_ANY_ID, NULL);
	if (dev) {
		result = acpi_processor_errata_piix4(dev);
		pci_dev_put(dev);
	}

	return result;
}