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
 int /*<<< orphan*/  ClearPageMappedToDisk (struct page*) ; 
 int EIO ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  cancel_dirty_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_page_mlock (struct page*) ; 
 int /*<<< orphan*/  do_invalidatepage (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ page_has_private (struct page*) ; 
 int /*<<< orphan*/  remove_from_page_cache (struct page*) ; 

__attribute__((used)) static int
truncate_complete_page(struct address_space *mapping, struct page *page)
{
	if (page->mapping != mapping)
		return -EIO;

	if (page_has_private(page))
		do_invalidatepage(page, 0);

	cancel_dirty_page(page, PAGE_CACHE_SIZE);

	clear_page_mlock(page);
	remove_from_page_cache(page);
	ClearPageMappedToDisk(page);
	page_cache_release(page);	/* pagecache ref */
	return 0;
}