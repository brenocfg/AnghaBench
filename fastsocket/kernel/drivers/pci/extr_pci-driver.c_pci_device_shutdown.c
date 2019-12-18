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
struct pci_driver {int /*<<< orphan*/  (* shutdown ) (struct pci_dev*) ;} ;
struct pci_dev {struct pci_driver* driver; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_msi_shutdown (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_msix_shutdown (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static void pci_device_shutdown(struct device *dev)
{
	struct pci_dev *pci_dev = to_pci_dev(dev);
	struct pci_driver *drv = pci_dev->driver;

	if (drv && drv->shutdown)
		drv->shutdown(pci_dev);
	pci_msi_shutdown(pci_dev);
	pci_msix_shutdown(pci_dev);
}