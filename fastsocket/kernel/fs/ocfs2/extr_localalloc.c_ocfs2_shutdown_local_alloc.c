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
struct ocfs2_super {scalar_t__ local_alloc_state; struct buffer_head* local_alloc_bh; int /*<<< orphan*/  slot_num; int /*<<< orphan*/  la_enable_wq; } ;
struct ocfs2_dinode {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct buffer_head {int /*<<< orphan*/  b_size; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GLOBAL_BITMAP_SYSTEM_INODE ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCAL_ALLOC_SYSTEM_INODE ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 scalar_t__ OCFS2_LA_DISABLED ; 
 scalar_t__ OCFS2_LA_UNUSED ; 
 int /*<<< orphan*/  OCFS2_WINDOW_MOVE_CREDITS ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_dinode*) ; 
 struct ocfs2_dinode* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ocfs2_dinode*,struct ocfs2_dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_clear_local_alloc (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_sync_local_to_main (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_dinode*,struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_wq ; 

void ocfs2_shutdown_local_alloc(struct ocfs2_super *osb)
{
	int status;
	handle_t *handle;
	struct inode *local_alloc_inode = NULL;
	struct buffer_head *bh = NULL;
	struct buffer_head *main_bm_bh = NULL;
	struct inode *main_bm_inode = NULL;
	struct ocfs2_dinode *alloc_copy = NULL;
	struct ocfs2_dinode *alloc = NULL;

	mlog_entry_void();

	cancel_delayed_work(&osb->la_enable_wq);
	flush_workqueue(ocfs2_wq);

	if (osb->local_alloc_state == OCFS2_LA_UNUSED)
		goto out;

	local_alloc_inode =
		ocfs2_get_system_file_inode(osb,
					    LOCAL_ALLOC_SYSTEM_INODE,
					    osb->slot_num);
	if (!local_alloc_inode) {
		status = -ENOENT;
		mlog_errno(status);
		goto out;
	}

	osb->local_alloc_state = OCFS2_LA_DISABLED;

	main_bm_inode = ocfs2_get_system_file_inode(osb,
						    GLOBAL_BITMAP_SYSTEM_INODE,
						    OCFS2_INVALID_SLOT);
	if (!main_bm_inode) {
		status = -EINVAL;
		mlog_errno(status);
		goto out;
	}

	mutex_lock(&main_bm_inode->i_mutex);

	status = ocfs2_inode_lock(main_bm_inode, &main_bm_bh, 1);
	if (status < 0) {
		mlog_errno(status);
		goto out_mutex;
	}

	/* WINDOW_MOVE_CREDITS is a bit heavy... */
	handle = ocfs2_start_trans(osb, OCFS2_WINDOW_MOVE_CREDITS);
	if (IS_ERR(handle)) {
		mlog_errno(PTR_ERR(handle));
		handle = NULL;
		goto out_unlock;
	}

	bh = osb->local_alloc_bh;
	alloc = (struct ocfs2_dinode *) bh->b_data;

	alloc_copy = kmalloc(bh->b_size, GFP_NOFS);
	if (!alloc_copy) {
		status = -ENOMEM;
		goto out_commit;
	}
	memcpy(alloc_copy, alloc, bh->b_size);

	status = ocfs2_journal_access_di(handle, INODE_CACHE(local_alloc_inode),
					 bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto out_commit;
	}

	ocfs2_clear_local_alloc(alloc);

	status = ocfs2_journal_dirty(handle, bh);
	if (status < 0) {
		mlog_errno(status);
		goto out_commit;
	}

	brelse(bh);
	osb->local_alloc_bh = NULL;
	osb->local_alloc_state = OCFS2_LA_UNUSED;

	status = ocfs2_sync_local_to_main(osb, handle, alloc_copy,
					  main_bm_inode, main_bm_bh);
	if (status < 0)
		mlog_errno(status);

out_commit:
	ocfs2_commit_trans(osb, handle);

out_unlock:
	brelse(main_bm_bh);

	ocfs2_inode_unlock(main_bm_inode, 1);

out_mutex:
	mutex_unlock(&main_bm_inode->i_mutex);
	iput(main_bm_inode);

out:
	if (local_alloc_inode)
		iput(local_alloc_inode);

	if (alloc_copy)
		kfree(alloc_copy);

	mlog_exit_void();
}