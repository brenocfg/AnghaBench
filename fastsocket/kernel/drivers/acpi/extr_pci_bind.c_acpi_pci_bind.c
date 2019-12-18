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
struct pci_dev {struct pci_bus* bus; struct pci_bus* subordinate; int /*<<< orphan*/  devfn; } ;
struct pci_bus {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {int (* bind ) (struct acpi_device*) ;int /*<<< orphan*/  unbind; } ;
struct acpi_device {int /*<<< orphan*/  handle; TYPE_1__ ops; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  METHOD_NAME__PRT ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_dev* acpi_get_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_pci_irq_add_prt (int /*<<< orphan*/ ,struct pci_bus*) ; 
 int /*<<< orphan*/  acpi_pci_unbind ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 

__attribute__((used)) static int acpi_pci_bind(struct acpi_device *device)
{
	acpi_status status;
	acpi_handle handle;
	struct pci_bus *bus;
	struct pci_dev *dev;

	dev = acpi_get_pci_dev(device->handle);
	if (!dev)
		return 0;

	/*
	 * Install the 'bind' function to facilitate callbacks for
	 * children of the P2P bridge.
	 */
	if (dev->subordinate) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Device %04x:%02x:%02x.%d is a PCI bridge\n",
				  pci_domain_nr(dev->bus), dev->bus->number,
				  PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn)));
		device->ops.bind = acpi_pci_bind;
		device->ops.unbind = acpi_pci_unbind;
	}

	/*
	 * Evaluate and parse _PRT, if exists.  This code allows parsing of
	 * _PRT objects within the scope of non-bridge devices.  Note that
	 * _PRTs within the scope of a PCI bridge assume the bridge's
	 * subordinate bus number.
	 *
	 * TBD: Can _PRTs exist within the scope of non-bridge PCI devices?
	 */
	status = acpi_get_handle(device->handle, METHOD_NAME__PRT, &handle);
	if (ACPI_FAILURE(status))
		goto out;

	if (dev->subordinate)
		bus = dev->subordinate;
	else
		bus = dev->bus;

	acpi_pci_irq_add_prt(device->handle, bus);

out:
	pci_dev_put(dev);
	return 0;
}