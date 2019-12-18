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
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int PCI_IOV_RESOURCES ; 
 int PCI_IOV_RESOURCE_END ; 
 int pci_sriov_resource_alignment (struct pci_dev*,int) ; 
 int resource_alignment (struct resource*) ; 

__attribute__((used)) static inline int pci_resource_alignment(struct pci_dev *dev,
					 struct resource *res)
{
#ifdef CONFIG_PCI_IOV
	int resno = res - dev->resource;

	if (resno >= PCI_IOV_RESOURCES && resno <= PCI_IOV_RESOURCE_END)
		return pci_sriov_resource_alignment(dev, resno);
#endif
	return resource_alignment(res);
}