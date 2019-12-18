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
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 unsigned long alloc_highmem ; 
 unsigned long alloc_normal ; 
 int /*<<< orphan*/  copy_bm ; 
 unsigned long count_data_pages () ; 
 scalar_t__ count_highmem_pages () ; 
 int /*<<< orphan*/  memory_bm_clear_bit (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long memory_bm_next_pfn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_bm_position_reset (int /*<<< orphan*/ *) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  swsusp_unset_page_forbidden (struct page*) ; 
 int /*<<< orphan*/  swsusp_unset_page_free (struct page*) ; 

__attribute__((used)) static void free_unnecessary_pages(void)
{
	unsigned long save, to_free_normal, to_free_highmem;

	save = count_data_pages();
	if (alloc_normal >= save) {
		to_free_normal = alloc_normal - save;
		save = 0;
	} else {
		to_free_normal = 0;
		save -= alloc_normal;
	}
	save += count_highmem_pages();
	if (alloc_highmem >= save) {
		to_free_highmem = alloc_highmem - save;
	} else {
		to_free_highmem = 0;
		save -= alloc_highmem;
		if (to_free_normal > save)
			to_free_normal -= save;
		else
			to_free_normal = 0;
	}

	memory_bm_position_reset(&copy_bm);

	while (to_free_normal > 0 || to_free_highmem > 0) {
		unsigned long pfn = memory_bm_next_pfn(&copy_bm);
		struct page *page = pfn_to_page(pfn);

		if (PageHighMem(page)) {
			if (!to_free_highmem)
				continue;
			to_free_highmem--;
			alloc_highmem--;
		} else {
			if (!to_free_normal)
				continue;
			to_free_normal--;
			alloc_normal--;
		}
		memory_bm_clear_bit(&copy_bm, pfn);
		swsusp_unset_page_forbidden(page);
		swsusp_unset_page_free(page);
		__free_page(page);
	}
}