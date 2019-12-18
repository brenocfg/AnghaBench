#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct address_space {TYPE_1__* a_ops; } ;
typedef  int isolate_mode_t ;
struct TYPE_2__ {int /*<<< orphan*/  migratepage; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageLRU (struct page*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ISOLATE_ACTIVE ; 
 int ISOLATE_ASYNC_MIGRATE ; 
 int ISOLATE_CLEAN ; 
 int ISOLATE_INACTIVE ; 
 int /*<<< orphan*/  PageActive (struct page*) ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageLRU (struct page*) ; 
 scalar_t__ PageUnevictable (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  get_page_unless_zero (struct page*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_is_file_cache (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 

int __isolate_lru_page(struct page *page, isolate_mode_t mode, int file)
{
	bool all_lru_mode;
	int ret = -EINVAL;

	/* Only take pages on the LRU. */
	if (!PageLRU(page))
		return ret;

	all_lru_mode = (mode & (ISOLATE_ACTIVE|ISOLATE_INACTIVE)) ==
		(ISOLATE_ACTIVE|ISOLATE_INACTIVE);

	/*
	 * When checking the active state, we need to be sure we are
	 * dealing with comparible boolean values.  Take the logical not
	 * of each.
	 */
	if (!all_lru_mode && !PageActive(page) != !(mode & ISOLATE_ACTIVE))
		return ret;

	if (!all_lru_mode && !!page_is_file_cache(page) != file)
		return ret;

	/*
	 * When this function is being called for lumpy reclaim, we
	 * initially look into all LRU pages, active, inactive and
	 * unevictable; only give shrink_page_list evictable pages.
	 */
	if (PageUnevictable(page))
		return ret;

	ret = -EBUSY;

	/*
	 * To minimise LRU disruption, the caller can indicate that it only
	 * wants to isolate pages it will be able to operate on without
	 * blocking - clean pages for the most part.
	 *
	 * ISOLATE_CLEAN means that only clean pages should be isolated. This
	 * is used by reclaim when it is cannot write to backing storage
	 *
	 * ISOLATE_ASYNC_MIGRATE is used to indicate that it only wants to pages
	 * that it is possible to migrate without blocking
	 */
	if (mode & (ISOLATE_CLEAN|ISOLATE_ASYNC_MIGRATE)) {
		/* All the caller can do on PageWriteback is block */
		if (PageWriteback(page))
			return ret;

		if (PageDirty(page)) {
			struct address_space *mapping;

			/* ISOLATE_CLEAN means only clean pages */
			if (mode & ISOLATE_CLEAN)
				return ret;

			/*
			 * Only pages without mappings or that have a
			 * ->migratepage callback are possible to migrate
			 * without blocking
			 */
			mapping = page_mapping(page);
			if (mapping && !mapping->a_ops->migratepage)
				return ret;
		}
	}

	if (likely(get_page_unless_zero(page))) {
		/*
		 * Be careful not to clear PageLRU until after we're
		 * sure the page is not being freed elsewhere -- the
		 * page release code relies on it.
		 */
		ClearPageLRU(page);
		ret = 0;
	}

	return ret;
}