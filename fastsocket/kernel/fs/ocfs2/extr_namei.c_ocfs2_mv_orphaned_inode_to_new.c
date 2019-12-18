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
struct ocfs2_super {int /*<<< orphan*/  sb; int /*<<< orphan*/  slot_num; } ;
struct ocfs2_dir_lookup_result {int /*<<< orphan*/ * member_0; } ;
struct ocfs2_dinode {scalar_t__ i_orphaned_slot; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_links_count; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/ * d_op; TYPE_1__ d_name; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  ip_blkno; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_ORPHANED_FL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ORPHAN_DIR_SYSTEM_INODE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocfs2_add_entry (int /*<<< orphan*/ *,struct dentry*,struct inode*,int /*<<< orphan*/ ,struct buffer_head*,struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_check_dir_for_entry (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_dentry_attach_lock (struct dentry*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_dentry_ops ; 
 int /*<<< orphan*/  ocfs2_free_dir_lookup_result (struct ocfs2_dir_lookup_result*) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_orphan_del (struct ocfs2_super*,int /*<<< orphan*/ *,struct inode*,struct inode*,struct buffer_head*) ; 
 int ocfs2_prepare_dir_for_insert (struct ocfs2_super*,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_rename_credits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 

int ocfs2_mv_orphaned_inode_to_new(struct inode *dir,
				   struct inode *inode,
				   struct dentry *dentry)
{
	int status = 0;
	struct buffer_head *parent_di_bh = NULL;
	handle_t *handle = NULL;
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	struct ocfs2_dinode *dir_di, *di;
	struct inode *orphan_dir_inode = NULL;
	struct buffer_head *orphan_dir_bh = NULL;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_dir_lookup_result lookup = { NULL, };

	mlog_entry("(0x%p, 0x%p, %.*s')\n", dir, dentry,
		   dentry->d_name.len, dentry->d_name.name);

	status = ocfs2_inode_lock(dir, &parent_di_bh, 1);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		return status;
	}

	dir_di = (struct ocfs2_dinode *) parent_di_bh->b_data;
	if (!dir_di->i_links_count) {
		/* can't make a file in a deleted directory. */
		status = -ENOENT;
		goto leave;
	}

	status = ocfs2_check_dir_for_entry(dir, dentry->d_name.name,
					   dentry->d_name.len);
	if (status)
		goto leave;

	/* get a spot inside the dir. */
	status = ocfs2_prepare_dir_for_insert(osb, dir, parent_di_bh,
					      dentry->d_name.name,
					      dentry->d_name.len, &lookup);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	orphan_dir_inode = ocfs2_get_system_file_inode(osb,
						       ORPHAN_DIR_SYSTEM_INODE,
						       osb->slot_num);
	if (!orphan_dir_inode) {
		status = -EEXIST;
		mlog_errno(status);
		goto leave;
	}

	mutex_lock(&orphan_dir_inode->i_mutex);

	status = ocfs2_inode_lock(orphan_dir_inode, &orphan_dir_bh, 1);
	if (status < 0) {
		mlog_errno(status);
		mutex_unlock(&orphan_dir_inode->i_mutex);
		iput(orphan_dir_inode);
		goto leave;
	}

	status = ocfs2_read_inode_block(inode, &di_bh);
	if (status < 0) {
		mlog_errno(status);
		goto orphan_unlock;
	}

	handle = ocfs2_start_trans(osb, ocfs2_rename_credits(osb->sb));
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto orphan_unlock;
	}

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode),
					 di_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto out_commit;
	}

	status = ocfs2_orphan_del(osb, handle, orphan_dir_inode, inode,
				  orphan_dir_bh);
	if (status < 0) {
		mlog_errno(status);
		goto out_commit;
	}

	di = (struct ocfs2_dinode *)di_bh->b_data;
	le32_add_cpu(&di->i_flags, -OCFS2_ORPHANED_FL);
	di->i_orphaned_slot = 0;
	ocfs2_journal_dirty(handle, di_bh);

	status = ocfs2_add_entry(handle, dentry, inode,
				 OCFS2_I(inode)->ip_blkno, parent_di_bh,
				 &lookup);
	if (status < 0) {
		mlog_errno(status);
		goto out_commit;
	}

	status = ocfs2_dentry_attach_lock(dentry, inode,
					  OCFS2_I(dir)->ip_blkno);
	if (status) {
		mlog_errno(status);
		goto out_commit;
	}

	insert_inode_hash(inode);
	dentry->d_op = &ocfs2_dentry_ops;
	d_instantiate(dentry, inode);
	status = 0;
out_commit:
	ocfs2_commit_trans(osb, handle);
orphan_unlock:
	ocfs2_inode_unlock(orphan_dir_inode, 1);
	mutex_unlock(&orphan_dir_inode->i_mutex);
	iput(orphan_dir_inode);
leave:

	ocfs2_inode_unlock(dir, 1);

	brelse(di_bh);
	brelse(parent_di_bh);
	brelse(orphan_dir_bh);

	ocfs2_free_dir_lookup_result(&lookup);

	mlog_exit(status);

	return status;
}