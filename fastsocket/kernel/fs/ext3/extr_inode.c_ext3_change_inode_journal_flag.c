#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_8__ {int h_sync; } ;
typedef  TYPE_1__ handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int EROFS ; 
 TYPE_7__* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/ * EXT3_JOURNAL (struct inode*) ; 
 int /*<<< orphan*/  EXT3_JOURNAL_DATA_FL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 TYPE_1__* ext3_journal_start (struct inode*,int) ; 
 int /*<<< orphan*/  ext3_journal_stop (TYPE_1__*) ; 
 int ext3_mark_inode_dirty (TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  ext3_set_aops (struct inode*) ; 
 int /*<<< orphan*/  ext3_std_error (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_journal_aborted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_lock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_unlock_updates (int /*<<< orphan*/ *) ; 

int ext3_change_inode_journal_flag(struct inode *inode, int val)
{
	journal_t *journal;
	handle_t *handle;
	int err;

	/*
	 * We have to be very careful here: changing a data block's
	 * journaling status dynamically is dangerous.  If we write a
	 * data block to the journal, change the status and then delete
	 * that block, we risk forgetting to revoke the old log record
	 * from the journal and so a subsequent replay can corrupt data.
	 * So, first we make sure that the journal is empty and that
	 * nobody is changing anything.
	 */

	journal = EXT3_JOURNAL(inode);
	if (is_journal_aborted(journal))
		return -EROFS;

	journal_lock_updates(journal);
	journal_flush(journal);

	/*
	 * OK, there are no updates running now, and all cached data is
	 * synced to disk.  We are now in a completely consistent state
	 * which doesn't have anything in the journal, and we know that
	 * no filesystem updates are running, so it is safe to modify
	 * the inode's in-core data-journaling state flag now.
	 */

	if (val)
		EXT3_I(inode)->i_flags |= EXT3_JOURNAL_DATA_FL;
	else
		EXT3_I(inode)->i_flags &= ~EXT3_JOURNAL_DATA_FL;
	ext3_set_aops(inode);

	journal_unlock_updates(journal);

	/* Finally we can mark the inode as dirty. */

	handle = ext3_journal_start(inode, 1);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	err = ext3_mark_inode_dirty(handle, inode);
	handle->h_sync = 1;
	ext3_journal_stop(handle);
	ext3_std_error(inode->i_sb, err);

	return err;
}