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
struct pci_dev {unsigned int devfn; } ;
struct hardware_path {scalar_t__* bc; scalar_t__ mod; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PCI_FUNC (unsigned int) ; 
 int PCI_SLOT (unsigned int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int match_pci_device(struct device *dev, int index,
		struct hardware_path *modpath)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	int id;

	if (index == 5) {
		/* we are at the end of the path, and on the actual device */
		unsigned int devfn = pdev->devfn;
		return ((modpath->bc[5] == PCI_SLOT(devfn)) &&
					(modpath->mod == PCI_FUNC(devfn)));
	}

	id = PCI_SLOT(pdev->devfn) | (PCI_FUNC(pdev->devfn) << 5);
	return (modpath->bc[index] == id);
}