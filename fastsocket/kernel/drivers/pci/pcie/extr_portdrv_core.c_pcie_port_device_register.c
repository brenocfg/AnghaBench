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

/* Variables and functions */
 int ENODEV ; 
 int PCIE_PORT_DEVICE_MAXSERVICES ; 
 int PCIE_PORT_SERVICE_VC ; 
 int /*<<< orphan*/  cleanup_service_irqs (struct pci_dev*) ; 
 int init_service_irqs (struct pci_dev*,int*,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcie_device_init (struct pci_dev*,int,int) ; 
 int pcie_get_port_device_capability (struct pci_dev*) ; 

int pcie_port_device_register(struct pci_dev *dev)
{
	int status, capabilities, i, nr_serv;
	int irqs[PCIE_PORT_DEVICE_MAXSERVICES];

	/* Get and check PCI Express port services */
	capabilities = pcie_get_port_device_capability(dev);
	if (!capabilities)
		return -ENODEV;

	status = pci_enable_device(dev);
	if (status)
		return status;
	pci_set_master(dev);

	/*
	 * Initialize service irqs. Don't use service devices that
	 * require interrupts if there is no way to generate them.
	 */
	status = init_service_irqs(dev, irqs, capabilities);
	if (status) {
		capabilities &= PCIE_PORT_SERVICE_VC;
		if (!capabilities)
			goto error_disable;
	}

	/* Allocate child services if any */
	for (i = 0, nr_serv = 0; i < PCIE_PORT_DEVICE_MAXSERVICES; i++) {
		int service = 1 << i;

		if (!(capabilities & service))
			continue;

		status = pcie_device_init(dev, service, irqs[i]);
		if (!status)
			nr_serv++;
	}
	if (!nr_serv) {
		pci_disable_device(dev);
		status = -ENODEV;
		goto error_cleanup_irqs;
	}

	return 0;

error_cleanup_irqs:
	cleanup_service_irqs(dev);
error_disable:
	pci_disable_device(dev);
	return status;
}