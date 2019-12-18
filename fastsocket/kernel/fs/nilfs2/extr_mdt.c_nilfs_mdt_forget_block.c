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
struct inode {unsigned long i_blkbits; int /*<<< orphan*/  i_mapping; } ;
struct buffer_head {int dummy; } ;
typedef  unsigned long pgoff_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 unsigned long PAGE_CACHE_SHIFT ; 
 int PageDirty (struct page*) ; 
 struct page* find_lock_page (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ invalidate_inode_pages2_range (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  nilfs_forget_buffer (struct buffer_head*) ; 
 struct buffer_head* nilfs_page_get_nth_block (struct page*,unsigned long) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

int nilfs_mdt_forget_block(struct inode *inode, unsigned long block)
{
	pgoff_t index = (pgoff_t)block >>
		(PAGE_CACHE_SHIFT - inode->i_blkbits);
	struct page *page;
	unsigned long first_block;
	int ret = 0;
	int still_dirty;

	page = find_lock_page(inode->i_mapping, index);
	if (!page)
		return -ENOENT;

	wait_on_page_writeback(page);

	first_block = (unsigned long)index <<
		(PAGE_CACHE_SHIFT - inode->i_blkbits);
	if (page_has_buffers(page)) {
		struct buffer_head *bh;

		bh = nilfs_page_get_nth_block(page, block - first_block);
		nilfs_forget_buffer(bh);
	}
	still_dirty = PageDirty(page);
	unlock_page(page);
	page_cache_release(page);

	if (still_dirty ||
	    invalidate_inode_pages2_range(inode->i_mapping, index, index) != 0)
		ret = -EBUSY;
	return ret;
}