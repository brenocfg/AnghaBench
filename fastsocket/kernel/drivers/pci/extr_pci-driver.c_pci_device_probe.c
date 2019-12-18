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
struct pci_driver {int dummy; } ;
struct pci_dev {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int __pci_device_probe (struct pci_driver*,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 struct pci_driver* to_pci_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_device_probe(struct device * dev)
{
	int error = 0;
	struct pci_driver *drv;
	struct pci_dev *pci_dev;

	drv = to_pci_driver(dev->driver);
	pci_dev = to_pci_dev(dev);
	pci_dev_get(pci_dev);
	error = __pci_device_probe(drv, pci_dev);
	if (error)
		pci_dev_put(pci_dev);

	return error;
}