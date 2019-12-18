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
struct TYPE_2__ {int (* set_page_dirty ) (struct page*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReclaim (struct page*) ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  TestSetPageDirty (struct page*) ; 
 int __set_page_dirty_buffers (struct page*) ; 
 scalar_t__ likely (struct address_space*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int stub1 (struct page*) ; 

int set_page_dirty(struct page *page)
{
	struct address_space *mapping = page_mapping(page);

	if (likely(mapping)) {
		int (*spd)(struct page *) = mapping->a_ops->set_page_dirty;
		/*
		 * readahead/lru_deactivate_page could remain
		 * PG_readahead/PG_reclaim due to race with end_page_writeback
		 * About readahead, if the page is written, the flags would be
		 * reset. So no problem.
		 * About lru_deactivate_page, if the page is redirty, the flag
		 * will be reset. So no problem. but if the page is used by readahead
		 * it will confuse readahead and make it restart the size rampup
		 * process. But it's a trivial problem.
		 */
		ClearPageReclaim(page);
#ifdef CONFIG_BLOCK
		if (!spd)
			spd = __set_page_dirty_buffers;
#endif
		return (*spd)(page);
	}
	if (!PageDirty(page)) {
		if (!TestSetPageDirty(page))
			return 1;
	}
	return 0;
}