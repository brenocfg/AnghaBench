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
struct page {struct page* first_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  __SetPageHead (struct page*) ; 
 int /*<<< orphan*/  __SetPageTail (struct page*) ; 
 struct page* mem_map_next (struct page*,struct page*,int) ; 
 int /*<<< orphan*/  set_compound_order (struct page*,unsigned long) ; 
 int /*<<< orphan*/  set_page_count (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prep_compound_gigantic_page(struct page *page, unsigned long order)
{
	int i;
	int nr_pages = 1 << order;
	struct page *p = page + 1;

	/* we rely on prep_new_huge_page to set the destructor */
	set_compound_order(page, order);
	__SetPageHead(page);
	for (i = 1; i < nr_pages; i++, p = mem_map_next(p, page, i)) {
		__SetPageTail(p);
		set_page_count(p, 0);
		p->first_page = page;
	}
}