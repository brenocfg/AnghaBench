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
struct super_block {int s_blocksize; } ;
struct reiserfs_transaction_handle {scalar_t__ t_trans_id; } ;
struct page {unsigned long index; } ;
struct inode {unsigned long i_size; int i_blkbits; struct super_block* i_sb; } ;
struct buffer_head {struct buffer_head* b_this_page; } ;

/* Variables and functions */
 unsigned long PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  buffer_dirty (struct buffer_head*) ; 
 int buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int journal_end (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,struct super_block*,struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  reiserfs_add_ordered_list (struct inode*,struct buffer_head*) ; 
 scalar_t__ reiserfs_data_ordered (struct super_block*) ; 
 int reiserfs_file_data_log (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,struct buffer_head*,int) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (struct super_block*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

int reiserfs_commit_page(struct inode *inode, struct page *page,
			 unsigned from, unsigned to)
{
	unsigned block_start, block_end;
	int partial = 0;
	unsigned blocksize;
	struct buffer_head *bh, *head;
	unsigned long i_size_index = inode->i_size >> PAGE_CACHE_SHIFT;
	int new;
	int logit = reiserfs_file_data_log(inode);
	struct super_block *s = inode->i_sb;
	int bh_per_page = PAGE_CACHE_SIZE / s->s_blocksize;
	struct reiserfs_transaction_handle th;
	int ret = 0;

	th.t_trans_id = 0;
	blocksize = 1 << inode->i_blkbits;

	if (logit) {
		reiserfs_write_lock(s);
		ret = journal_begin(&th, s, bh_per_page + 1);
		if (ret)
			goto drop_write_lock;
		reiserfs_update_inode_transaction(inode);
	}
	for (bh = head = page_buffers(page), block_start = 0;
	     bh != head || !block_start;
	     block_start = block_end, bh = bh->b_this_page) {

		new = buffer_new(bh);
		clear_buffer_new(bh);
		block_end = block_start + blocksize;
		if (block_end <= from || block_start >= to) {
			if (!buffer_uptodate(bh))
				partial = 1;
		} else {
			set_buffer_uptodate(bh);
			if (logit) {
				reiserfs_prepare_for_journal(s, bh, 1);
				journal_mark_dirty(&th, s, bh);
			} else if (!buffer_dirty(bh)) {
				mark_buffer_dirty(bh);
				/* do data=ordered on any page past the end
				 * of file and any buffer marked BH_New.
				 */
				if (reiserfs_data_ordered(inode->i_sb) &&
				    (new || page->index >= i_size_index)) {
					reiserfs_add_ordered_list(inode, bh);
				}
			}
		}
	}
	if (logit) {
		ret = journal_end(&th, s, bh_per_page + 1);
	      drop_write_lock:
		reiserfs_write_unlock(s);
	}
	/*
	 * If this is a partial write which happened to make all buffers
	 * uptodate then we can optimize away a bogus readpage() for
	 * the next read(). Here we 'discover' whether the page went
	 * uptodate as a result of this (potentially partial) write.
	 */
	if (!partial)
		SetPageUptodate(page);
	return ret;
}