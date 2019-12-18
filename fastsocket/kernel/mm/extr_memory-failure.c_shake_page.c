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
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int /*<<< orphan*/  drain_all_pages () ; 
 scalar_t__ is_free_buddy_page (struct page*) ; 
 int /*<<< orphan*/  lru_add_drain_all () ; 
 int page_count (struct page*) ; 
 int shrink_slab (int,int /*<<< orphan*/ ,int) ; 

void shake_page(struct page *p, int access)
{
	if (!PageSlab(p)) {
		lru_add_drain_all();
		if (PageLRU(p))
			return;
		drain_all_pages();
		if (PageLRU(p) || is_free_buddy_page(p))
			return;
	}

	/*
	 * Only call shrink_slab here (which would also shrink other caches) if
	 * access is not potentially fatal.
	 */
	if (access) {
		int nr;
		do {
			nr = shrink_slab(1000, GFP_KERNEL, 1000);
			if (page_count(p) == 1)
				break;
		} while (nr > 10);
	}
}