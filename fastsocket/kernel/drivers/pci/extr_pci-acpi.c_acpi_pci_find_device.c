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
struct pci_dev {int /*<<< orphan*/  devfn; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int acpi_integer ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_child (int /*<<< orphan*/ ,int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int acpi_pci_find_device(struct device *dev, acpi_handle *handle)
{
	struct pci_dev * pci_dev;
	acpi_integer	addr;

	pci_dev = to_pci_dev(dev);
	/* Please ref to ACPI spec for the syntax of _ADR */
	addr = (PCI_SLOT(pci_dev->devfn) << 16) | PCI_FUNC(pci_dev->devfn);
	*handle = acpi_get_child(DEVICE_ACPI_HANDLE(dev->parent), addr);
	if (!*handle)
		return -ENODEV;
	return 0;
}