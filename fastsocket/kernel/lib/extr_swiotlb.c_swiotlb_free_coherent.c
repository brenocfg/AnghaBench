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
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_to_phys (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_unmap_single (struct device*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  is_swiotlb_buffer (int /*<<< orphan*/ ) ; 

void
swiotlb_free_coherent(struct device *hwdev, size_t size, void *vaddr,
		      dma_addr_t dev_addr)
{
	phys_addr_t paddr = dma_to_phys(hwdev, dev_addr);

	WARN_ON(irqs_disabled());
	if (!is_swiotlb_buffer(paddr))
		free_pages((unsigned long)vaddr, get_order(size));
	else
		/* DMA_TO_DEVICE to avoid memcpy in unmap_single */
		do_unmap_single(hwdev, vaddr, size, DMA_TO_DEVICE);
}