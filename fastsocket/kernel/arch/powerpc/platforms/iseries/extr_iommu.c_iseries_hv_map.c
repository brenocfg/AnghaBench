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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  iommu_map_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vio_iommu_table ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

dma_addr_t iseries_hv_map(void *vaddr, size_t size,
			enum dma_data_direction direction)
{
	return iommu_map_page(NULL, &vio_iommu_table, virt_to_page(vaddr),
			      (unsigned long)vaddr % PAGE_SIZE, size,
			      DMA_BIT_MASK(32), direction, NULL);
}