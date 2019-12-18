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
struct resource {int dummy; } ;
struct pci_dev {int dummy; } ;
typedef  enum pci_bar_type { ____Placeholder_pci_bar_type } pci_bar_type ;

/* Variables and functions */
 int /*<<< orphan*/  __pci_read_base (struct pci_dev*,int,struct resource*,int) ; 
 int pci_iov_resource_bar (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_sriov_enabled ; 
 int resource_alignment (struct resource*) ; 

int pci_sriov_resource_alignment(struct pci_dev *dev, int resno)
{
	struct resource tmp;
	enum pci_bar_type type;
	int reg = pci_iov_resource_bar(dev, resno, &type);

	if (!pci_sriov_enabled)
		return 0;

	if (!reg)
		return 0;

	 __pci_read_base(dev, type, &tmp, reg);
	return resource_alignment(&tmp);
}