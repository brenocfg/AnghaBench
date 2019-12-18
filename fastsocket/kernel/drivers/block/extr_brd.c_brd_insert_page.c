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
struct page {int index; } ;
struct brd_device {int /*<<< orphan*/  brd_lock; int /*<<< orphan*/  brd_pages; } ;
typedef  int sector_t ;
typedef  int pgoff_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GFP_NOIO ; 
 int PAGE_SECTORS_SHIFT ; 
 int __GFP_HIGHMEM ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int) ; 
 struct page* brd_lookup_page (struct brd_device*,int) ; 
 scalar_t__ radix_tree_insert (int /*<<< orphan*/ *,int,struct page*) ; 
 struct page* radix_tree_lookup (int /*<<< orphan*/ *,int) ; 
 scalar_t__ radix_tree_preload (int) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *brd_insert_page(struct brd_device *brd, sector_t sector)
{
	pgoff_t idx;
	struct page *page;
	gfp_t gfp_flags;

	page = brd_lookup_page(brd, sector);
	if (page)
		return page;

	/*
	 * Must use NOIO because we don't want to recurse back into the
	 * block or filesystem layers from page reclaim.
	 *
	 * Cannot support XIP and highmem, because our ->direct_access
	 * routine for XIP must return memory that is always addressable.
	 * If XIP was reworked to use pfns and kmap throughout, this
	 * restriction might be able to be lifted.
	 */
	gfp_flags = GFP_NOIO | __GFP_ZERO;
#ifndef CONFIG_BLK_DEV_XIP
	gfp_flags |= __GFP_HIGHMEM;
#endif
	page = alloc_page(gfp_flags);
	if (!page)
		return NULL;

	if (radix_tree_preload(GFP_NOIO)) {
		__free_page(page);
		return NULL;
	}

	spin_lock(&brd->brd_lock);
	idx = sector >> PAGE_SECTORS_SHIFT;
	if (radix_tree_insert(&brd->brd_pages, idx, page)) {
		__free_page(page);
		page = radix_tree_lookup(&brd->brd_pages, idx);
		BUG_ON(!page);
		BUG_ON(page->index != idx);
	} else
		page->index = idx;
	spin_unlock(&brd->brd_lock);

	radix_tree_preload_end();

	return page;
}