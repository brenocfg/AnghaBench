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
struct page {int dummy; } ;
struct dma_attrs {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_NONE ; 
 scalar_t__ dma_capable (struct device*,int /*<<< orphan*/ ,size_t) ; 
 void* io_tlb_overflow_buffer ; 
 void* map_single (struct device*,scalar_t__,size_t,int) ; 
 scalar_t__ page_to_phys (struct page*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  phys_to_dma (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  swiotlb_force ; 
 int /*<<< orphan*/  swiotlb_full (struct device*,size_t,int,int) ; 
 int /*<<< orphan*/  swiotlb_virt_to_bus (struct device*,void*) ; 

dma_addr_t swiotlb_map_page(struct device *dev, struct page *page,
			    unsigned long offset, size_t size,
			    enum dma_data_direction dir,
			    struct dma_attrs *attrs)
{
	phys_addr_t phys = page_to_phys(page) + offset;
	dma_addr_t dev_addr = phys_to_dma(dev, phys);
	void *map;

	BUG_ON(dir == DMA_NONE);
	/*
	 * If the address happens to be in the device's DMA window,
	 * we can safely return the device addr and not worry about bounce
	 * buffering it.
	 */
	if (dma_capable(dev, dev_addr, size) && !swiotlb_force)
		return dev_addr;

	/*
	 * Oh well, have to allocate and map a bounce buffer.
	 */
	map = map_single(dev, phys, size, dir);
	if (!map) {
		swiotlb_full(dev, size, dir, 1);
		map = io_tlb_overflow_buffer;
	}

	dev_addr = swiotlb_virt_to_bus(dev, map);

	/*
	 * Ensure that the address returned is DMA'ble
	 */
	if (!dma_capable(dev, dev_addr, size))
		panic("map_single: bounce buffer is not DMA'ble");

	return dev_addr;
}