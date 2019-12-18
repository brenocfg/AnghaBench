#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct agp_memory {int page_count; struct page** pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_memory_agp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (struct page*) ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pages_array_wb (struct page**,int) ; 
 int /*<<< orphan*/  unmap_page_from_agp (struct page*) ; 

void agp_generic_destroy_pages(struct agp_memory *mem)
{
	int i;
	struct page *page;

	if (!mem)
		return;

#ifdef CONFIG_X86
	set_pages_array_wb(mem->pages, mem->page_count);
#endif

	for (i = 0; i < mem->page_count; i++) {
		page = mem->pages[i];

#ifndef CONFIG_X86
		unmap_page_from_agp(page);
#endif
		put_page(page);
		__free_page(page);
		atomic_dec(&agp_bridge->current_memory_agp);
		mem->pages[i] = NULL;
	}
}