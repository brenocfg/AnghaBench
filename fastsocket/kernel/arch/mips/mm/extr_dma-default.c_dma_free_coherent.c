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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long CAC_ADDR (unsigned long) ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ dma_release_from_coherent (struct device*,int,void*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int get_order (size_t) ; 
 int /*<<< orphan*/  plat_device_is_coherent (struct device*) ; 
 int /*<<< orphan*/  plat_unmap_dma_mem (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

void dma_free_coherent(struct device *dev, size_t size, void *vaddr,
	dma_addr_t dma_handle)
{
	unsigned long addr = (unsigned long) vaddr;
	int order = get_order(size);

	if (dma_release_from_coherent(dev, order, vaddr))
		return;

	plat_unmap_dma_mem(dev, dma_handle, size, DMA_BIDIRECTIONAL);

	if (!plat_device_is_coherent(dev))
		addr = CAC_ADDR(addr);

	free_pages(addr, get_order(size));
}