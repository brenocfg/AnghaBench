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

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int __GFP_FS ; 
 struct page* __page_cache_alloc (int) ; 
 scalar_t__ add_to_page_cache_lru (struct page*,struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* find_get_page (struct address_space*,int /*<<< orphan*/ ) ; 
 int mapping_gfp_mask (struct address_space*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ trylock_page (struct page*) ; 

struct page *
grab_cache_page_nowait(struct address_space *mapping, pgoff_t index)
{
	struct page *page = find_get_page(mapping, index);

	if (page) {
		if (trylock_page(page))
			return page;
		page_cache_release(page);
		return NULL;
	}
	page = __page_cache_alloc(mapping_gfp_mask(mapping) & ~__GFP_FS);
	if (page && add_to_page_cache_lru(page, mapping, index, GFP_NOFS)) {
		page_cache_release(page);
		page = NULL;
	}
	return page;
}