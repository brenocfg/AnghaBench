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
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_FROM_DEVICE ; 
 int DMA_NONE ; 
 int /*<<< orphan*/  dma_mark_clean (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dma_to_phys (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_unmap_single (struct device*,int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ is_swiotlb_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmap_single(struct device *hwdev, dma_addr_t dev_addr,
			 size_t size, int dir)
{
	phys_addr_t paddr = dma_to_phys(hwdev, dev_addr);

	BUG_ON(dir == DMA_NONE);

	if (is_swiotlb_buffer(paddr)) {
		do_unmap_single(hwdev, phys_to_virt(paddr), size, dir);
		return;
	}

	if (dir != DMA_FROM_DEVICE)
		return;

	/*
	 * phys_to_virt doesn't work with hihgmem page but we could
	 * call dma_mark_clean() with hihgmem page here. However, we
	 * are fine since dma_mark_clean() is null on POWERPC. We can
	 * make dma_mark_clean() take a physical address if necessary.
	 */
	dma_mark_clean(phys_to_virt(paddr), size);
}