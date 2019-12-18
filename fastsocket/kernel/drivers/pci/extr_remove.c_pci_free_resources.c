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
struct resource {scalar_t__ parent; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int PCI_NUM_RESOURCES ; 
 int /*<<< orphan*/  msi_remove_pci_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_cleanup_rom (struct pci_dev*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 

__attribute__((used)) static void pci_free_resources(struct pci_dev *dev)
{
	int i;

 	msi_remove_pci_irq_vectors(dev);

	pci_cleanup_rom(dev);
	for (i = 0; i < PCI_NUM_RESOURCES; i++) {
		struct resource *res = dev->resource + i;
		if (res->parent)
			release_resource(res);
	}
}