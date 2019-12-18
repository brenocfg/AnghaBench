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

/* Variables and functions */
 unsigned int PCI_FUNC (int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_device (unsigned int,unsigned int,struct pci_dev*) ; 

__attribute__((used)) static struct pci_dev *pci_get_device_func(unsigned vendor,
					   unsigned device,
					   unsigned func)
{
	struct pci_dev *ret = NULL;

	while (1) {
		ret = pci_get_device(vendor, device, ret);

		if (!ret)
			break;

		if (PCI_FUNC(ret->devfn) == func)
			break;
	}

	return ret;
}