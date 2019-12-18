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
struct scatterlist {int /*<<< orphan*/  length; int /*<<< orphan*/  dma_address; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  __dma_sync (unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plat_device_is_coherent (struct device*) ; 
 int /*<<< orphan*/  plat_unmap_dma_mem (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sg_virt (struct scatterlist*) ; 

void dma_unmap_sg(struct device *dev, struct scatterlist *sg, int nhwentries,
	enum dma_data_direction direction)
{
	unsigned long addr;
	int i;

	BUG_ON(direction == DMA_NONE);

	for (i = 0; i < nhwentries; i++, sg++) {
		if (!plat_device_is_coherent(dev) &&
		    direction != DMA_TO_DEVICE) {
			addr = (unsigned long) sg_virt(sg);
			if (addr)
				__dma_sync(addr, sg->length, direction);
		}
		plat_unmap_dma_mem(dev, sg->dma_address, sg->length, direction);
	}
}