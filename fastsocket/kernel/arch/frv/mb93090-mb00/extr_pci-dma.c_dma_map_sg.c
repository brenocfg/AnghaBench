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
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_NONE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __KM_CACHE ; 
 unsigned long __get_DAMPR (int) ; 
 int /*<<< orphan*/  __set_DAMPR (int,unsigned long) ; 
 int /*<<< orphan*/  __set_IAMPR (int,unsigned long) ; 
 int /*<<< orphan*/  frv_dcache_writeback (unsigned long,scalar_t__) ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

int dma_map_sg(struct device *dev, struct scatterlist *sg, int nents,
	       enum dma_data_direction direction)
{
	unsigned long dampr2;
	void *vaddr;
	int i;

	BUG_ON(direction == DMA_NONE);

	dampr2 = __get_DAMPR(2);

	for (i = 0; i < nents; i++) {
		vaddr = kmap_atomic(sg_page(&sg[i]), __KM_CACHE);

		frv_dcache_writeback((unsigned long) vaddr,
				     (unsigned long) vaddr + PAGE_SIZE);

	}

	kunmap_atomic(vaddr, __KM_CACHE);
	if (dampr2) {
		__set_DAMPR(2, dampr2);
		__set_IAMPR(2, dampr2);
	}

	return nents;
}