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
struct st_buffer {int buffer_size; int use_sg; int frp_segs; int reserved_page_order; struct page** reserved_pages; int /*<<< orphan*/  b_data; scalar_t__ cleared; } ;
struct page {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int ST_MAX_ORDER ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages (int,int) ; 
 int /*<<< orphan*/  normalize_buffer (struct st_buffer*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

__attribute__((used)) static int enlarge_buffer(struct st_buffer * STbuffer, int new_size, int need_dma)
{
	int segs, nbr, max_segs, b_size, order, got;
	gfp_t priority;

	if (new_size <= STbuffer->buffer_size)
		return 1;

	if (STbuffer->buffer_size <= PAGE_SIZE)
		normalize_buffer(STbuffer);  /* Avoid extra segment */

	max_segs = STbuffer->use_sg;
	nbr = max_segs - STbuffer->frp_segs;
	if (nbr <= 0)
		return 0;

	priority = GFP_KERNEL | __GFP_NOWARN;
	if (need_dma)
		priority |= GFP_DMA;

	if (STbuffer->cleared)
		priority |= __GFP_ZERO;

	if (STbuffer->frp_segs) {
		order = STbuffer->reserved_page_order;
		b_size = PAGE_SIZE << order;
	} else {
		for (b_size = PAGE_SIZE, order = 0;
		     order < ST_MAX_ORDER &&
			     max_segs * (PAGE_SIZE << order) < new_size;
		     order++, b_size *= 2)
			;  /* empty */
		STbuffer->reserved_page_order = order;
	}
	if (max_segs * (PAGE_SIZE << order) < new_size) {
		if (order == ST_MAX_ORDER)
			return 0;
		normalize_buffer(STbuffer);
		return enlarge_buffer(STbuffer, new_size, need_dma);
	}

	for (segs = STbuffer->frp_segs, got = STbuffer->buffer_size;
	     segs < max_segs && got < new_size;) {
		struct page *page;

		page = alloc_pages(priority, order);
		if (!page) {
			DEB(STbuffer->buffer_size = got);
			normalize_buffer(STbuffer);
			return 0;
		}

		STbuffer->frp_segs += 1;
		got += b_size;
		STbuffer->buffer_size = got;
		STbuffer->reserved_pages[segs] = page;
		segs++;
	}
	STbuffer->b_data = page_address(STbuffer->reserved_pages[0]);

	return 1;
}