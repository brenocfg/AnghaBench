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
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dma_free_coherent (struct device*,size_t,void*,unsigned long) ; 
 scalar_t__ dma_release_from_coherent (struct device*,int,void*) ; 
 int get_order (size_t) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 

void dma_free_coherent(struct device *dev, size_t size,
			 void *vaddr, dma_addr_t dma_handle)
{
	int order = get_order(size);
	unsigned long pfn = dma_handle >> PAGE_SHIFT;
	int k;

	WARN_ON(irqs_disabled());	/* for portability */

	if (dma_release_from_coherent(dev, order, vaddr))
		return;

	debug_dma_free_coherent(dev, size, vaddr, dma_handle);
	for (k = 0; k < (1 << order); k++)
		__free_pages(pfn_to_page(pfn + k), 0);
	iounmap(vaddr);
}