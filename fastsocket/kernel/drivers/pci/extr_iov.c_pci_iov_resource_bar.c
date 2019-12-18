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
struct pci_dev {TYPE_1__* sriov; int /*<<< orphan*/  is_physfn; } ;
typedef  enum pci_bar_type { ____Placeholder_pci_bar_type } pci_bar_type ;
struct TYPE_2__ {int pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PCI_IOV_RESOURCES ; 
 int PCI_IOV_RESOURCE_END ; 
 int PCI_SRIOV_BAR ; 
 int pci_bar_unknown ; 

int pci_iov_resource_bar(struct pci_dev *dev, int resno,
			 enum pci_bar_type *type)
{
	if (resno < PCI_IOV_RESOURCES || resno > PCI_IOV_RESOURCE_END)
		return 0;

	BUG_ON(!dev->is_physfn);

	*type = pci_bar_unknown;

	return dev->sriov->pos + PCI_SRIOV_BAR +
		4 * (resno - PCI_IOV_RESOURCES);
}