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
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int /*<<< orphan*/  __nilfs_clear_page_dirty (struct page*) ; 
 int /*<<< orphan*/  __nilfs_end_page_io (struct page*,int) ; 
 scalar_t__ buffer_nilfs_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ nilfs_page_buffers_clean (struct page*) ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void nilfs_end_page_io(struct page *page, int err)
{
	if (!page)
		return;

	if (buffer_nilfs_node(page_buffers(page)) && !PageWriteback(page)) {
		/*
		 * For b-tree node pages, this function may be called twice
		 * or more because they might be split in a segment.
		 */
		if (PageDirty(page)) {
			/*
			 * For pages holding split b-tree node buffers, dirty
			 * flag on the buffers may be cleared discretely.
			 * In that case, the page is once redirtied for
			 * remaining buffers, and it must be cancelled if
			 * all the buffers get cleaned later.
			 */
			lock_page(page);
			if (nilfs_page_buffers_clean(page))
				__nilfs_clear_page_dirty(page);
			unlock_page(page);
		}
		return;
	}

	__nilfs_end_page_io(page, err);
}