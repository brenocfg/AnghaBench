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

/* Variables and functions */
 int /*<<< orphan*/  __dma_sync (void*,size_t,int) ; 
 int /*<<< orphan*/  __dma_sync_page_highmem (struct page*,unsigned long,size_t,int) ; 
 scalar_t__ page_address (struct page*) ; 

void __dma_sync_page(struct page *page, unsigned long offset,
	size_t size, int direction)
{
#ifdef CONFIG_HIGHMEM
	__dma_sync_page_highmem(page, offset, size, direction);
#else
	unsigned long start = (unsigned long)page_address(page) + offset;
	__dma_sync((void *)start, size, direction);
#endif
}