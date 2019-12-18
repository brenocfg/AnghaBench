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
struct snd_emu10k1_memblk {int dummy; } ;
struct snd_emu10k1 {int dma_mask; int /*<<< orphan*/ * page_ptr_table; int /*<<< orphan*/ * page_addr_table; int /*<<< orphan*/  memhdr; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  __synth_free_pages (struct snd_emu10k1*,int,int) ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  emu10k1_memblk_init (struct snd_emu10k1_memblk*) ; 
 int /*<<< orphan*/  get_single_page_range (int /*<<< orphan*/ ,struct snd_emu10k1_memblk*,int*,int*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 

__attribute__((used)) static int synth_alloc_pages(struct snd_emu10k1 *emu, struct snd_emu10k1_memblk *blk)
{
	int page, first_page, last_page;

	emu10k1_memblk_init(blk);
	get_single_page_range(emu->memhdr, blk, &first_page, &last_page);
	/* allocate kernel pages */
	for (page = first_page; page <= last_page; page++) {
		/* first try to allocate from <4GB zone */
		struct page *p = alloc_page(GFP_KERNEL | GFP_DMA32 |
					    __GFP_NOWARN);
		if (!p || (page_to_pfn(p) & ~(emu->dma_mask >> PAGE_SHIFT))) {
			if (p)
				__free_page(p);
			/* try to allocate from <16MB zone */
			p = alloc_page(GFP_ATOMIC | GFP_DMA |
				       __GFP_NORETRY | /* no OOM-killer */
				       __GFP_NOWARN);
		}
		if (!p) {
			__synth_free_pages(emu, first_page, page - 1);
			return -ENOMEM;
		}
		emu->page_addr_table[page] = page_to_phys(p);
		emu->page_ptr_table[page] = page_address(p);
	}
	return 0;
}