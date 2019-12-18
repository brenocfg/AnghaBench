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
struct reiserfs_journal_list {int dummy; } ;
struct reiserfs_journal {int /*<<< orphan*/  j_dirty_buffers_lock; struct reiserfs_journal_list* j_current_jl; } ;
struct reiserfs_jh {struct reiserfs_journal_list* jl; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {struct reiserfs_jh* b_private; } ;

/* Variables and functions */
 struct reiserfs_journal* SB_JOURNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_journal_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_journaled (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 scalar_t__ reiserfs_file_data_log (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_free_jh (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int invalidatepage_can_drop(struct inode *inode, struct buffer_head *bh)
{
	int ret = 1;
	struct reiserfs_journal *j = SB_JOURNAL(inode->i_sb);

	lock_buffer(bh);
	spin_lock(&j->j_dirty_buffers_lock);
	if (!buffer_mapped(bh)) {
		goto free_jh;
	}
	/* the page is locked, and the only places that log a data buffer
	 * also lock the page.
	 */
	if (reiserfs_file_data_log(inode)) {
		/*
		 * very conservative, leave the buffer pinned if
		 * anyone might need it.
		 */
		if (buffer_journaled(bh) || buffer_journal_dirty(bh)) {
			ret = 0;
		}
	} else  if (buffer_dirty(bh)) {
		struct reiserfs_journal_list *jl;
		struct reiserfs_jh *jh = bh->b_private;

		/* why is this safe?
		 * reiserfs_setattr updates i_size in the on disk
		 * stat data before allowing vmtruncate to be called.
		 *
		 * If buffer was put onto the ordered list for this
		 * transaction, we know for sure either this transaction
		 * or an older one already has updated i_size on disk,
		 * and this ordered data won't be referenced in the file
		 * if we crash.
		 *
		 * if the buffer was put onto the ordered list for an older
		 * transaction, we need to leave it around
		 */
		if (jh && (jl = jh->jl)
		    && jl != SB_JOURNAL(inode->i_sb)->j_current_jl)
			ret = 0;
	}
      free_jh:
	if (ret && bh->b_private) {
		reiserfs_free_jh(bh);
	}
	spin_unlock(&j->j_dirty_buffers_lock);
	unlock_buffer(bh);
	return ret;
}