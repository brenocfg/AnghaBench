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
struct ocfs2_truncate_log {int /*<<< orphan*/  tl_used; } ;
struct ocfs2_super {struct buffer_head* osb_tl_bh; struct inode* osb_tl_inode; } ;
struct TYPE_3__ {struct ocfs2_truncate_log i_dealloc; } ;
struct ocfs2_dinode {TYPE_1__ id2; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GLOBAL_BITMAP_SYSTEM_INODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DINODE (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  OCFS2_TRUNCATE_LOG_UPDATE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_replay_truncate_records (struct ocfs2_super*,int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 

int __ocfs2_flush_truncate_log(struct ocfs2_super *osb)
{
	int status;
	unsigned int num_to_flush;
	handle_t *handle;
	struct inode *tl_inode = osb->osb_tl_inode;
	struct inode *data_alloc_inode = NULL;
	struct buffer_head *tl_bh = osb->osb_tl_bh;
	struct buffer_head *data_alloc_bh = NULL;
	struct ocfs2_dinode *di;
	struct ocfs2_truncate_log *tl;

	mlog_entry_void();

	BUG_ON(mutex_trylock(&tl_inode->i_mutex));

	di = (struct ocfs2_dinode *) tl_bh->b_data;

	/* tl_bh is loaded from ocfs2_truncate_log_init().  It's validated
	 * by the underlying call to ocfs2_read_inode_block(), so any
	 * corruption is a code bug */
	BUG_ON(!OCFS2_IS_VALID_DINODE(di));

	tl = &di->id2.i_dealloc;
	num_to_flush = le16_to_cpu(tl->tl_used);
	mlog(0, "Flush %u records from truncate log #%llu\n",
	     num_to_flush, (unsigned long long)OCFS2_I(tl_inode)->ip_blkno);
	if (!num_to_flush) {
		status = 0;
		goto out;
	}

	data_alloc_inode = ocfs2_get_system_file_inode(osb,
						       GLOBAL_BITMAP_SYSTEM_INODE,
						       OCFS2_INVALID_SLOT);
	if (!data_alloc_inode) {
		status = -EINVAL;
		mlog(ML_ERROR, "Could not get bitmap inode!\n");
		goto out;
	}

	mutex_lock(&data_alloc_inode->i_mutex);

	status = ocfs2_inode_lock(data_alloc_inode, &data_alloc_bh, 1);
	if (status < 0) {
		mlog_errno(status);
		goto out_mutex;
	}

	handle = ocfs2_start_trans(osb, OCFS2_TRUNCATE_LOG_UPDATE);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto out_unlock;
	}

	status = ocfs2_replay_truncate_records(osb, handle, data_alloc_inode,
					       data_alloc_bh);
	if (status < 0)
		mlog_errno(status);

	ocfs2_commit_trans(osb, handle);

out_unlock:
	brelse(data_alloc_bh);
	ocfs2_inode_unlock(data_alloc_inode, 1);

out_mutex:
	mutex_unlock(&data_alloc_inode->i_mutex);
	iput(data_alloc_inode);

out:
	mlog_exit(status);
	return status;
}