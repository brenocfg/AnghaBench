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
struct page {int /*<<< orphan*/ * shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_pages (struct page*,int) ; 
 int /*<<< orphan*/  kmemcheck_page_is_tracked (struct page*) ; 
 int /*<<< orphan*/  kmemcheck_show_pages (struct page*,int) ; 
 struct page* virt_to_page (int /*<<< orphan*/ *) ; 

void kmemcheck_free_shadow(struct page *page, int order)
{
	struct page *shadow;
	int pages;
	int i;

	if (!kmemcheck_page_is_tracked(page))
		return;

	pages = 1 << order;

	kmemcheck_show_pages(page, pages);

	shadow = virt_to_page(page[0].shadow);

	for(i = 0; i < pages; ++i)
		page[i].shadow = NULL;

	__free_pages(shadow, order);
}