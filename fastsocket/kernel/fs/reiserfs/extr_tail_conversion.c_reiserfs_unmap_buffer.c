#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct reiserfs_journal {int /*<<< orphan*/  j_dirty_buffers_lock; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int /*<<< orphan*/ * b_bdev; int /*<<< orphan*/  b_assoc_buffers; TYPE_2__* b_page; scalar_t__ b_private; } ;
struct TYPE_4__ {TYPE_1__* mapping; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct reiserfs_journal* SB_JOURNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_journal_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_journaled (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_req (struct buffer_head*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_free_jh (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

void reiserfs_unmap_buffer(struct buffer_head *bh)
{
	lock_buffer(bh);
	if (buffer_journaled(bh) || buffer_journal_dirty(bh)) {
		BUG();
	}
	clear_buffer_dirty(bh);
	/* Remove the buffer from whatever list it belongs to. We are mostly
	   interested in removing it from per-sb j_dirty_buffers list, to avoid
	   BUG() on attempt to write not mapped buffer */
	if ((!list_empty(&bh->b_assoc_buffers) || bh->b_private) && bh->b_page) {
		struct inode *inode = bh->b_page->mapping->host;
		struct reiserfs_journal *j = SB_JOURNAL(inode->i_sb);
		spin_lock(&j->j_dirty_buffers_lock);
		list_del_init(&bh->b_assoc_buffers);
		reiserfs_free_jh(bh);
		spin_unlock(&j->j_dirty_buffers_lock);
	}
	clear_buffer_mapped(bh);
	clear_buffer_req(bh);
	clear_buffer_new(bh);
	bh->b_bdev = NULL;
	unlock_buffer(bh);
}