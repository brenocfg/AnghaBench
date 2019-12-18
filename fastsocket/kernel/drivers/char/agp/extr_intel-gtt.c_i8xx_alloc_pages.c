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
struct TYPE_2__ {int /*<<< orphan*/  current_memory_agp; } ;

/* Variables and functions */
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  __free_pages (struct page*,int) ; 
 TYPE_1__* agp_bridge ; 
 struct page* alloc_pages (int,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ set_pages_uc (struct page*,int) ; 
 int /*<<< orphan*/  set_pages_wb (struct page*,int) ; 

__attribute__((used)) static struct page *i8xx_alloc_pages(void)
{
	struct page *page;

	page = alloc_pages(GFP_KERNEL | GFP_DMA32, 2);
	if (page == NULL)
		return NULL;

	if (set_pages_uc(page, 4) < 0) {
		set_pages_wb(page, 4);
		__free_pages(page, 2);
		return NULL;
	}
	get_page(page);
	atomic_inc(&agp_bridge->current_memory_agp);
	return page;
}