#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct inode {scalar_t__ i_blocks; scalar_t__ i_size; int /*<<< orphan*/  i_data; } ;
struct TYPE_9__ {int h_sync; } ;
typedef  TYPE_1__ handle_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_dtime; } ;

/* Variables and functions */
 TYPE_8__* EXT3_I (struct inode*) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  ext3_free_inode (TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  ext3_journal_stop (TYPE_1__*) ; 
 scalar_t__ ext3_mark_inode_dirty (TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  ext3_orphan_del (TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  ext3_truncate (struct inode*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 TYPE_1__* start_transaction (struct inode*) ; 
 int /*<<< orphan*/  trace_ext3_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ext3_delete_inode (struct inode * inode)
{
	handle_t *handle;

	truncate_inode_pages(&inode->i_data, 0);

	if (is_bad_inode(inode))
		goto no_delete;

	trace_ext3_delete_inode(inode);
	handle = start_transaction(inode);
	if (IS_ERR(handle)) {
		/*
		 * If we're going to skip the normal cleanup, we still need to
		 * make sure that the in-core orphan linked list is properly
		 * cleaned up.
		 */
		ext3_orphan_del(NULL, inode);
		goto no_delete;
	}

	if (IS_SYNC(inode))
		handle->h_sync = 1;
	inode->i_size = 0;
	if (inode->i_blocks)
		ext3_truncate(inode);
	/*
	 * Kill off the orphan record which ext3_truncate created.
	 * AKPM: I think this can be inside the above `if'.
	 * Note that ext3_orphan_del() has to be able to cope with the
	 * deletion of a non-existent orphan - this is because we don't
	 * know if ext3_truncate() actually created an orphan record.
	 * (Well, we could do this if we need to, but heck - it works)
	 */
	ext3_orphan_del(handle, inode);
	EXT3_I(inode)->i_dtime	= get_seconds();

	/*
	 * One subtle ordering requirement: if anything has gone wrong
	 * (transaction abort, IO errors, whatever), then we can still
	 * do these next steps (the fs will already have been marked as
	 * having errors), but we can't free the inode if the mark_dirty
	 * fails.
	 */
	if (ext3_mark_inode_dirty(handle, inode))
		/* If that failed, just do the required in-core inode clear. */
		clear_inode(inode);
	else
		ext3_free_inode(handle, inode);
	ext3_journal_stop(handle);
	return;
no_delete:
	clear_inode(inode);	/* We must guarantee clearing of inode... */
}