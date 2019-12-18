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
struct backing_dev_info {int dummy; } ;
struct address_space {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; struct backing_dev_info* backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_WRITEBACK ; 
 int /*<<< orphan*/  NR_WRITEBACK ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGECACHE_TAG_TOWRITE ; 
 int /*<<< orphan*/  PAGECACHE_TAG_WRITEBACK ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int TestSetPageWriteback (struct page*) ; 
 int /*<<< orphan*/  __inc_bdi_stat (struct backing_dev_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ bdi_cap_account_writeback (struct backing_dev_info*) ; 
 int /*<<< orphan*/  inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  radix_tree_tag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int test_set_page_writeback(struct page *page)
{
	struct address_space *mapping = page_mapping(page);
	int ret;

	if (mapping) {
		struct backing_dev_info *bdi = mapping->backing_dev_info;
		unsigned long flags;

		spin_lock_irqsave(&mapping->tree_lock, flags);
		ret = TestSetPageWriteback(page);
		if (!ret) {
			radix_tree_tag_set(&mapping->page_tree,
						page_index(page),
						PAGECACHE_TAG_WRITEBACK);
			if (bdi_cap_account_writeback(bdi))
				__inc_bdi_stat(bdi, BDI_WRITEBACK);
		}
		if (!PageDirty(page))
			radix_tree_tag_clear(&mapping->page_tree,
						page_index(page),
						PAGECACHE_TAG_DIRTY);
		radix_tree_tag_clear(&mapping->page_tree,
				     page_index(page),
				     PAGECACHE_TAG_TOWRITE);
		spin_unlock_irqrestore(&mapping->tree_lock, flags);
	} else {
		ret = TestSetPageWriteback(page);
	}
	if (!ret)
		inc_zone_page_state(page, NR_WRITEBACK);
	return ret;

}