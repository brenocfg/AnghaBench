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
 int /*<<< orphan*/  PCI_ANY_ID ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_subsys (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 

struct pci_dev *pci_find_device(unsigned int vendor, unsigned int device,
				struct pci_dev *from)
{
	struct pci_dev *pdev;

	pci_dev_get(from);
	pdev = pci_get_subsys(vendor, device, PCI_ANY_ID, PCI_ANY_ID, from);
	pci_dev_put(pdev);
	return pdev;
}