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
struct scatterlist {int /*<<< orphan*/  length; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  flush_kernel_dcache_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_virt_addr (struct scatterlist*) ; 

__attribute__((used)) static void pa11_dma_unmap_sg(struct device *dev, struct scatterlist *sglist, int nents, enum dma_data_direction direction)
{
	int i;

	BUG_ON(direction == DMA_NONE);

	if (direction == DMA_TO_DEVICE)
	    return;

	/* once we do combining we'll need to use phys_to_virt(sg_dma_address(sglist)) */

	for (i = 0; i < nents; i++, sglist++ )
		flush_kernel_dcache_range(sg_virt_addr(sglist), sglist->length);
	return;
}