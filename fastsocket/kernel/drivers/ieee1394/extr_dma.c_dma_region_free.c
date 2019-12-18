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
struct dma_region {scalar_t__ n_pages; int /*<<< orphan*/ * kvirt; int /*<<< orphan*/ * sglist; int /*<<< orphan*/ * dev; scalar_t__ n_dma_pages; int /*<<< orphan*/  direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void dma_region_free(struct dma_region *dma)
{
	if (dma->n_dma_pages) {
		pci_unmap_sg(dma->dev, dma->sglist, dma->n_pages,
			     dma->direction);
		dma->n_dma_pages = 0;
		dma->dev = NULL;
	}

	vfree(dma->sglist);
	dma->sglist = NULL;

	vfree(dma->kvirt);
	dma->kvirt = NULL;
	dma->n_pages = 0;
}