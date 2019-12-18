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
struct dma_buffparms {int mapping_flags; int buffsize; int /*<<< orphan*/ * raw_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReserved (struct page*) ; 
 int DMA_MAP_MAPPED ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 struct page* virt_to_page (unsigned long) ; 

__attribute__((used)) static void sound_free_dmap(struct dma_buffparms *dmap)
{
	int sz, size;
	struct page *page;
	unsigned long start_addr, end_addr;

	if (dmap->raw_buf == NULL)
		return;
	if (dmap->mapping_flags & DMA_MAP_MAPPED)
		return;		/* Don't free mmapped buffer. Will use it next time */
	for (sz = 0, size = PAGE_SIZE; size < dmap->buffsize; sz++, size <<= 1);

	start_addr = (unsigned long) dmap->raw_buf;
	end_addr = start_addr + dmap->buffsize;

	for (page = virt_to_page(start_addr); page <= virt_to_page(end_addr); page++)
		ClearPageReserved(page);

	free_pages((unsigned long) dmap->raw_buf, sz);
	dmap->raw_buf = NULL;
}