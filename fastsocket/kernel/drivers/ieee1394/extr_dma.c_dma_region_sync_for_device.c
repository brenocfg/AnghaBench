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
struct dma_region {int /*<<< orphan*/  direction; int /*<<< orphan*/ * sglist; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int dma_region_find (struct dma_region*,unsigned long,int,unsigned long*) ; 
 int /*<<< orphan*/  pci_dma_sync_sg_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void dma_region_sync_for_device(struct dma_region *dma, unsigned long offset,
				unsigned long len)
{
	int first, last;
	unsigned long rem = 0;

	if (!len)
		len = 1;

	first = dma_region_find(dma, offset, 0, &rem);
	last = dma_region_find(dma, rem + len - 1, first, &rem);

	pci_dma_sync_sg_for_device(dma->dev, &dma->sglist[first],
				   last - first + 1, dma->direction);
}