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
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int EEXIST ; 
 int GFP_RECLAIM_MASK ; 
 struct page* __page_cache_alloc (int) ; 
 int add_to_page_cache_lru (struct page*,struct address_space*,int /*<<< orphan*/ ,int) ; 
 struct page* find_lock_page (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ unlikely (int) ; 

struct page *find_or_create_page(struct address_space *mapping,
		pgoff_t index, gfp_t gfp_mask)
{
	struct page *page;
	int err;
repeat:
	page = find_lock_page(mapping, index);
	if (!page) {
		page = __page_cache_alloc(gfp_mask);
		if (!page)
			return NULL;
		/*
		 * We want a regular kernel memory (not highmem or DMA etc)
		 * allocation for the radix tree nodes, but we need to honour
		 * the context-specific requirements the caller has asked for.
		 * GFP_RECLAIM_MASK collects those requirements.
		 */
		err = add_to_page_cache_lru(page, mapping, index,
			(gfp_mask & GFP_RECLAIM_MASK));
		if (unlikely(err)) {
			page_cache_release(page);
			page = NULL;
			if (err == -EEXIST)
				goto repeat;
		}
	}
	return page;
}