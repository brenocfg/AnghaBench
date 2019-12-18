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
struct page {int /*<<< orphan*/  shadow; } ;

/* Variables and functions */
 int PageCompound (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 scalar_t__ kmemcheck_page_is_tracked (struct page*) ; 
 int /*<<< orphan*/  page_count (struct page*) ; 
 int /*<<< orphan*/  set_page_refcounted (struct page*) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

void split_page(struct page *page, unsigned int order)
{
	int i;

	VM_BUG_ON(PageCompound(page));
	VM_BUG_ON(!page_count(page));

#ifdef CONFIG_KMEMCHECK
	/*
	 * Split shadow pages too, because free(page[0]) would
	 * otherwise free the whole shadow.
	 */
	if (kmemcheck_page_is_tracked(page))
		split_page(virt_to_page(page[0].shadow), order);
#endif

	for (i = 1; i < (1 << order); i++)
		set_page_refcounted(page + i);
}