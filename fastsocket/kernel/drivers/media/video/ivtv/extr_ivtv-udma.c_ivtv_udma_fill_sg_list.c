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
struct ivtv_user_dma {int /*<<< orphan*/ ** map; int /*<<< orphan*/ * SGlist; int /*<<< orphan*/ ** bouncemap; } ;
struct ivtv_dma_page_info {int offset; int page_count; int tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KM_BOUNCE_READ ; 
 int PAGE_SIZE ; 
 scalar_t__ PageHighMem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alloc_page (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,unsigned int) ; 
 scalar_t__ page_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int) ; 

int ivtv_udma_fill_sg_list (struct ivtv_user_dma *dma, struct ivtv_dma_page_info *dma_page, int map_offset)
{
	int i, offset;
	unsigned long flags;

	if (map_offset < 0)
		return map_offset;

	offset = dma_page->offset;

	/* Fill SG Array with new values */
	for (i = 0; i < dma_page->page_count; i++) {
		unsigned int len = (i == dma_page->page_count - 1) ?
			dma_page->tail : PAGE_SIZE - offset;

		if (PageHighMem(dma->map[map_offset])) {
			void *src;

			if (dma->bouncemap[map_offset] == NULL)
				dma->bouncemap[map_offset] = alloc_page(GFP_KERNEL);
			if (dma->bouncemap[map_offset] == NULL)
				return -1;
			local_irq_save(flags);
			src = kmap_atomic(dma->map[map_offset], KM_BOUNCE_READ) + offset;
			memcpy(page_address(dma->bouncemap[map_offset]) + offset, src, len);
			kunmap_atomic(src, KM_BOUNCE_READ);
			local_irq_restore(flags);
			sg_set_page(&dma->SGlist[map_offset], dma->bouncemap[map_offset], len, offset);
		}
		else {
			sg_set_page(&dma->SGlist[map_offset], dma->map[map_offset], len, offset);
		}
		offset = 0;
		map_offset++;
	}
	return map_offset;
}