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
struct page {struct address_space* mapping; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  do_invalidatepage (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ page_has_private (struct page*) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void read_cache_pages_invalidate_page(struct address_space *mapping,
					     struct page *page)
{
	if (page_has_private(page)) {
		if (!trylock_page(page))
			BUG();
		page->mapping = mapping;
		do_invalidatepage(page, 0);
		page->mapping = NULL;
		unlock_page(page);
	}
	page_cache_release(page);
}