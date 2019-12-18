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
struct inode {unsigned int i_size; } ;
struct file {TYPE_1__* f_mapping; } ;
struct address_space {int dummy; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int PAGE_CACHE_SIZE ; 
 unsigned int block_write_end (struct file*,struct address_space*,int,unsigned int,unsigned int,struct page*,void*) ; 
 scalar_t__ ext3_can_truncate (struct inode*) ; 
 int /*<<< orphan*/ * ext3_journal_current_handle () ; 
 int ext3_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext3_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext3_truncate_failed_write (struct inode*) ; 
 int /*<<< orphan*/  journal_dirty_data_fn ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  trace_ext3_ordered_write_end (struct inode*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  update_file_sizes (struct inode*,int,unsigned int) ; 
 int walk_page_buffers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext3_ordered_write_end(struct file *file,
				struct address_space *mapping,
				loff_t pos, unsigned len, unsigned copied,
				struct page *page, void *fsdata)
{
	handle_t *handle = ext3_journal_current_handle();
	struct inode *inode = file->f_mapping->host;
	unsigned from, to;
	int ret = 0, ret2;

	trace_ext3_ordered_write_end(inode, pos, len, copied);
	copied = block_write_end(file, mapping, pos, len, copied, page, fsdata);

	from = pos & (PAGE_CACHE_SIZE - 1);
	to = from + copied;
	ret = walk_page_buffers(handle, page_buffers(page),
		from, to, NULL, journal_dirty_data_fn);

	if (ret == 0)
		update_file_sizes(inode, pos, copied);
	/*
	 * There may be allocated blocks outside of i_size because
	 * we failed to copy some data. Prepare for truncate.
	 */
	if (pos + len > inode->i_size && ext3_can_truncate(inode))
		ext3_orphan_add(handle, inode);
	ret2 = ext3_journal_stop(handle);
	if (!ret)
		ret = ret2;
	unlock_page(page);
	page_cache_release(page);

	if (pos + len > inode->i_size)
		ext3_truncate_failed_write(inode);
	return ret ? ret : copied;
}