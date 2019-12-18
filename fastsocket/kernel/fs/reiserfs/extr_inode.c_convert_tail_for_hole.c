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
struct page {unsigned long index; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct buffer_head {int b_size; struct page* b_page; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  fix_tail_page_for_writing (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 struct page* grab_cache_page (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int reiserfs_commit_write (int /*<<< orphan*/ *,struct page*,unsigned long,unsigned long) ; 
 int reiserfs_prepare_write (int /*<<< orphan*/ *,struct page*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int convert_tail_for_hole(struct inode *inode,
				 struct buffer_head *bh_result,
				 loff_t tail_offset)
{
	unsigned long index;
	unsigned long tail_end;
	unsigned long tail_start;
	struct page *tail_page;
	struct page *hole_page = bh_result->b_page;
	int retval = 0;

	if ((tail_offset & (bh_result->b_size - 1)) != 1)
		return -EIO;

	/* always try to read until the end of the block */
	tail_start = tail_offset & (PAGE_CACHE_SIZE - 1);
	tail_end = (tail_start | (bh_result->b_size - 1)) + 1;

	index = tail_offset >> PAGE_CACHE_SHIFT;
	/* hole_page can be zero in case of direct_io, we are sure
	   that we cannot get here if we write with O_DIRECT into
	   tail page */
	if (!hole_page || index != hole_page->index) {
		tail_page = grab_cache_page(inode->i_mapping, index);
		retval = -ENOMEM;
		if (!tail_page) {
			goto out;
		}
	} else {
		tail_page = hole_page;
	}

	/* we don't have to make sure the conversion did not happen while
	 ** we were locking the page because anyone that could convert
	 ** must first take i_mutex.
	 **
	 ** We must fix the tail page for writing because it might have buffers
	 ** that are mapped, but have a block number of 0.  This indicates tail
	 ** data that has been read directly into the page, and block_prepare_write
	 ** won't trigger a get_block in this case.
	 */
	fix_tail_page_for_writing(tail_page);
	retval = reiserfs_prepare_write(NULL, tail_page, tail_start, tail_end);
	if (retval)
		goto unlock;

	/* tail conversion might change the data in the page */
	flush_dcache_page(tail_page);

	retval = reiserfs_commit_write(NULL, tail_page, tail_start, tail_end);

      unlock:
	if (tail_page != hole_page) {
		unlock_page(tail_page);
		page_cache_release(tail_page);
	}
      out:
	return retval;
}