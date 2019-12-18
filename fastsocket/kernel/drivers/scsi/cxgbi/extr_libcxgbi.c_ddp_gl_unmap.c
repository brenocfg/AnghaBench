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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cxgbi_gather_list {int nelem; int /*<<< orphan*/ * phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ddp_gl_unmap(struct pci_dev *pdev,
					struct cxgbi_gather_list *gl)
{
	int i;

	for (i = 0; i < gl->nelem; i++)
		dma_unmap_page(&pdev->dev, gl->phys_addr[i], PAGE_SIZE,
				PCI_DMA_FROMDEVICE);
}