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
struct device {int /*<<< orphan*/ * parent; int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; } ;
struct pcie_device {int irq; int service; struct device device; struct pci_dev* port; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  get_descriptor_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct pcie_device*) ; 
 struct pcie_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_port_bus_type ; 
 int /*<<< orphan*/  release_pcie_device ; 

__attribute__((used)) static int pcie_device_init(struct pci_dev *pdev, int service, int irq)
{
	int retval;
	struct pcie_device *pcie;
	struct device *device;

	pcie = kzalloc(sizeof(*pcie), GFP_KERNEL);
	if (!pcie)
		return -ENOMEM;
	pcie->port = pdev;
	pcie->irq = irq;
	pcie->service = service;

	/* Initialize generic device interface */
	device = &pcie->device;
	device->bus = &pcie_port_bus_type;
	device->release = release_pcie_device;	/* callback to free pcie dev */
	dev_set_name(device, "%s:pcie%02x",
		     pci_name(pdev),
		     get_descriptor_id(pci_pcie_type(pdev), service));
	device->parent = &pdev->dev;

	retval = device_register(device);
	if (retval)
		kfree(pcie);
	else
		get_device(device);
	return retval;
}