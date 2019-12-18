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
struct list_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int nilfs_copy_replace_page_buffers (struct page*,struct list_head*) ; 
 scalar_t__ nilfs_test_page_to_be_frozen (struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int nilfs_begin_page_io(struct page *page, struct list_head *out)
{
	if (!page || PageWriteback(page))
		/* For split b-tree node pages, this function may be called
		   twice.  We ignore the 2nd or later calls by this check. */
		return 0;

	lock_page(page);
	clear_page_dirty_for_io(page);
	set_page_writeback(page);
	unlock_page(page);

	if (nilfs_test_page_to_be_frozen(page)) {
		int err = nilfs_copy_replace_page_buffers(page, out);
		if (unlikely(err))
			return err;
	}
	return 0;
}