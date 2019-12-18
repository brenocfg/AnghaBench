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
struct vme_dma_pci {int /*<<< orphan*/  address; void* private; int /*<<< orphan*/  type; } ;
struct vme_dma_attr {int /*<<< orphan*/  address; void* private; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VME_DMA_PCI ; 
 int /*<<< orphan*/  kfree (struct vme_dma_pci*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

struct vme_dma_attr *vme_dma_pci_attribute(dma_addr_t address)
{
	struct vme_dma_attr *attributes;
	struct vme_dma_pci *pci_attr;

	/* XXX Run some sanity checks here */

	attributes = (struct vme_dma_attr *)kmalloc(
		sizeof(struct vme_dma_attr), GFP_KERNEL);
	if(attributes == NULL) {
		printk("Unable to allocate memory for attributes structure\n");
		goto err_attr;
	}

	pci_attr = (struct vme_dma_pci *)kmalloc(sizeof(struct vme_dma_pci),
		GFP_KERNEL);
	if(pci_attr == NULL) {
		printk("Unable to allocate memory for pci attributes\n");
		goto err_pci;
	}



	attributes->type = VME_DMA_PCI;
	attributes->private = (void *)pci_attr;

	pci_attr->address = address;

	return attributes;

	kfree(pci_attr);
err_pci:
	kfree(attributes);
err_attr:
	return NULL;
}