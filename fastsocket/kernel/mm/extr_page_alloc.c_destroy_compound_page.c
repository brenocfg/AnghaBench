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
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  PageTail (struct page*) ; 
 int /*<<< orphan*/  __ClearPageHead (struct page*) ; 
 int /*<<< orphan*/  __ClearPageTail (struct page*) ; 
 int /*<<< orphan*/  bad_page (struct page*) ; 
 unsigned long compound_order (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int destroy_compound_page(struct page *page, unsigned long order)
{
	int i;
	int nr_pages = 1 << order;
	int bad = 0;

	if (unlikely(compound_order(page) != order) ||
	    unlikely(!PageHead(page))) {
		bad_page(page);
		bad++;
	}

	__ClearPageHead(page);

	for (i = 1; i < nr_pages; i++) {
		struct page *p = page + i;

		if (unlikely(!PageTail(p) || (p->first_page != page))) {
			bad_page(page);
			bad++;
		}
		__ClearPageTail(p);
	}

	return bad;
}