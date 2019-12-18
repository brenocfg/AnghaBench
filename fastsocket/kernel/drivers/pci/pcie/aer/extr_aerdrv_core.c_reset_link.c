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
struct pcie_port_service_driver {scalar_t__ (* reset_link ) (struct pci_dev*) ;} ;
struct pci_dev {int hdr_type; int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
typedef  scalar_t__ pci_ers_result_t ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ PCI_ERS_RESULT_DISCONNECT ; 
 scalar_t__ PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ PCI_EXP_TYPE_DOWNSTREAM ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 int PCI_HEADER_TYPE_BRIDGE ; 
 scalar_t__ default_reset_link (struct pci_dev*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct pcie_port_service_driver* find_aer_service (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 scalar_t__ stub1 (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t reset_link(struct pci_dev *dev)
{
	struct pci_dev *udev;
	pci_ers_result_t status;
	struct pcie_port_service_driver *driver;

	if (dev->hdr_type & PCI_HEADER_TYPE_BRIDGE) {
		/* Reset this port for all subordinates */
		udev = dev;
	} else {
		/* Reset the upstream component (likely downstream port) */
		udev = dev->bus->self;
	}

	/* Use the aer driver of the component firstly */
	driver = find_aer_service(udev);

	if (driver && driver->reset_link) {
		status = driver->reset_link(udev);
	} else if (pci_pcie_type(udev) == PCI_EXP_TYPE_DOWNSTREAM ||
		pci_pcie_type(udev) == PCI_EXP_TYPE_ROOT_PORT) {
		status = default_reset_link(udev);
	} else {
		dev_printk(KERN_DEBUG, &dev->dev,
			"no link-reset support at upstream device %s\n",
			pci_name(udev));
		return PCI_ERS_RESULT_DISCONNECT;
	}

	if (status != PCI_ERS_RESULT_RECOVERED) {
		dev_printk(KERN_DEBUG, &dev->dev,
			"link reset at upstream device %s failed\n",
			pci_name(udev));
		return PCI_ERS_RESULT_DISCONNECT;
	}

	return status;
}