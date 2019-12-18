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
struct inode {int /*<<< orphan*/  i_sb; scalar_t__ i_blocks; scalar_t__ i_size; int /*<<< orphan*/  i_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_dtime; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ blocks_for_truncate (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  ext4_begin_ordered_truncate (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_inode (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_handle_has_enough_credits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int ext4_journal_extend (int /*<<< orphan*/ *,int) ; 
 int ext4_journal_restart (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_should_order_data (struct inode*) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_warning (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_seconds () ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ext4_delete_inode(struct inode *inode)
{
	handle_t *handle;
	int err;

	if (ext4_should_order_data(inode))
		ext4_begin_ordered_truncate(inode, 0);
	truncate_inode_pages(&inode->i_data, 0);

	if (is_bad_inode(inode))
		goto no_delete;

	/*
	 * Protect us against freezing - iput() caller didn't have to have any
	 * protection against it
	 */
	sb_start_intwrite(inode->i_sb);
	handle = ext4_journal_start(inode, blocks_for_truncate(inode)+3);
	if (IS_ERR(handle)) {
		ext4_std_error(inode->i_sb, PTR_ERR(handle));
		/*
		 * If we're going to skip the normal cleanup, we still need to
		 * make sure that the in-core orphan linked list is properly
		 * cleaned up.
		 */
		ext4_orphan_del(NULL, inode);
		sb_end_intwrite(inode->i_sb);
		goto no_delete;
	}

	if (IS_SYNC(inode))
		ext4_handle_sync(handle);
	inode->i_size = 0;
	err = ext4_mark_inode_dirty(handle, inode);
	if (err) {
		ext4_warning(inode->i_sb,
			     "couldn't mark inode dirty (err %d)", err);
		goto stop_handle;
	}
	if (inode->i_blocks)
		ext4_truncate(inode);

	/*
	 * ext4_ext_truncate() doesn't reserve any slop when it
	 * restarts journal transactions; therefore there may not be
	 * enough credits left in the handle to remove the inode from
	 * the orphan list and set the dtime field.
	 */
	if (!ext4_handle_has_enough_credits(handle, 3)) {
		err = ext4_journal_extend(handle, 3);
		if (err > 0)
			err = ext4_journal_restart(handle, 3);
		if (err != 0) {
			ext4_warning(inode->i_sb,
				     "couldn't extend journal (err %d)", err);
		stop_handle:
			ext4_journal_stop(handle);
			sb_end_intwrite(inode->i_sb);
			goto no_delete;
		}
	}

	/*
	 * Kill off the orphan record which ext4_truncate created.
	 * AKPM: I think this can be inside the above `if'.
	 * Note that ext4_orphan_del() has to be able to cope with the
	 * deletion of a non-existent orphan - this is because we don't
	 * know if ext4_truncate() actually created an orphan record.
	 * (Well, we could do this if we need to, but heck - it works)
	 */
	ext4_orphan_del(handle, inode);
	EXT4_I(inode)->i_dtime	= get_seconds();

	/*
	 * One subtle ordering requirement: if anything has gone wrong
	 * (transaction abort, IO errors, whatever), then we can still
	 * do these next steps (the fs will already have been marked as
	 * having errors), but we can't free the inode if the mark_dirty
	 * fails.
	 */
	if (ext4_mark_inode_dirty(handle, inode))
		/* If that failed, just do the required in-core inode clear. */
		clear_inode(inode);
	else
		ext4_free_inode(handle, inode);
	ext4_journal_stop(handle);
	sb_end_intwrite(inode->i_sb);
	return;
no_delete:
	clear_inode(inode);	/* We must guarantee clearing of inode... */
}