#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ocfs2_super {int /*<<< orphan*/  sb; struct inode* root_inode; } ;
struct ocfs2_dir_lookup_result {int /*<<< orphan*/ * member_0; } ;
struct ocfs2_dinode {int dummy; } ;
struct inode {int i_nlink; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; TYPE_1__* d_parent; struct inode* d_inode; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {scalar_t__ ip_blkno; int /*<<< orphan*/  ip_flags; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 int EPERM ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_ORPHAN_NAMELEN ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OI_LS_PARENT ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 scalar_t__ inode_is_unlinkable (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_delete_entry (int /*<<< orphan*/ *,struct inode*,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_empty_dir (struct inode*) ; 
 int ocfs2_find_files_on_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,struct inode*,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_free_dir_lookup_result (struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int ocfs2_inode_lock_nested (struct inode*,struct buffer_head**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int ocfs2_orphan_add (struct ocfs2_super*,int /*<<< orphan*/ *,struct inode*,struct ocfs2_dinode*,char*,struct ocfs2_dir_lookup_result*,struct inode*) ; 
 int ocfs2_prepare_orphan_dir (struct ocfs2_super*,struct inode**,scalar_t__,char*,struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_remote_dentry_delete (struct dentry*) ; 
 int /*<<< orphan*/  ocfs2_set_links_count (struct ocfs2_dinode*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_unlink_credits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_unlink(struct inode *dir,
			struct dentry *dentry)
{
	int status;
	int child_locked = 0;
	struct inode *inode = dentry->d_inode;
	struct inode *orphan_dir = NULL;
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	u64 blkno;
	struct ocfs2_dinode *fe = NULL;
	struct buffer_head *fe_bh = NULL;
	struct buffer_head *parent_node_bh = NULL;
	handle_t *handle = NULL;
	char orphan_name[OCFS2_ORPHAN_NAMELEN + 1];
	struct ocfs2_dir_lookup_result lookup = { NULL, };
	struct ocfs2_dir_lookup_result orphan_insert = { NULL, };

	mlog_entry("(0x%p, 0x%p, '%.*s')\n", dir, dentry,
		   dentry->d_name.len, dentry->d_name.name);

	BUG_ON(dentry->d_parent->d_inode != dir);

	mlog(0, "ino = %llu\n", (unsigned long long)OCFS2_I(inode)->ip_blkno);

	if (inode == osb->root_inode) {
		mlog(0, "Cannot delete the root directory\n");
		return -EPERM;
	}

	status = ocfs2_inode_lock_nested(dir, &parent_node_bh, 1,
					 OI_LS_PARENT);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		return status;
	}

	status = ocfs2_find_files_on_disk(dentry->d_name.name,
					  dentry->d_name.len, &blkno, dir,
					  &lookup);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		goto leave;
	}

	if (OCFS2_I(inode)->ip_blkno != blkno) {
		status = -ENOENT;

		mlog(0, "ip_blkno %llu != dirent blkno %llu ip_flags = %x\n",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno,
		     (unsigned long long)blkno, OCFS2_I(inode)->ip_flags);
		goto leave;
	}

	status = ocfs2_inode_lock(inode, &fe_bh, 1);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		goto leave;
	}
	child_locked = 1;

	if (S_ISDIR(inode->i_mode)) {
		if (inode->i_nlink != 2 || !ocfs2_empty_dir(inode)) {
			status = -ENOTEMPTY;
			goto leave;
		}
	}

	status = ocfs2_remote_dentry_delete(dentry);
	if (status < 0) {
		/* This remote delete should succeed under all normal
		 * circumstances. */
		mlog_errno(status);
		goto leave;
	}

	if (inode_is_unlinkable(inode)) {
		status = ocfs2_prepare_orphan_dir(osb, &orphan_dir,
						  OCFS2_I(inode)->ip_blkno,
						  orphan_name, &orphan_insert);
		if (status < 0) {
			mlog_errno(status);
			goto leave;
		}
	}

	handle = ocfs2_start_trans(osb, ocfs2_unlink_credits(osb->sb));
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto leave;
	}

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), fe_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	fe = (struct ocfs2_dinode *) fe_bh->b_data;

	if (inode_is_unlinkable(inode)) {
		status = ocfs2_orphan_add(osb, handle, inode, fe, orphan_name,
					  &orphan_insert, orphan_dir);
		if (status < 0) {
			mlog_errno(status);
			goto leave;
		}
	}

	/* delete the name from the parent dir */
	status = ocfs2_delete_entry(handle, dir, &lookup);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	if (S_ISDIR(inode->i_mode))
		drop_nlink(inode);
	drop_nlink(inode);
	ocfs2_set_links_count(fe, inode->i_nlink);

	status = ocfs2_journal_dirty(handle, fe_bh);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	dir->i_ctime = dir->i_mtime = CURRENT_TIME;
	if (S_ISDIR(inode->i_mode))
		drop_nlink(dir);

	status = ocfs2_mark_inode_dirty(handle, dir, parent_node_bh);
	if (status < 0) {
		mlog_errno(status);
		if (S_ISDIR(inode->i_mode))
			inc_nlink(dir);
	}

leave:
	if (handle)
		ocfs2_commit_trans(osb, handle);

	if (child_locked)
		ocfs2_inode_unlock(inode, 1);

	ocfs2_inode_unlock(dir, 1);

	if (orphan_dir) {
		/* This was locked for us in ocfs2_prepare_orphan_dir() */
		ocfs2_inode_unlock(orphan_dir, 1);
		mutex_unlock(&orphan_dir->i_mutex);
		iput(orphan_dir);
	}

	brelse(fe_bh);
	brelse(parent_node_bh);

	ocfs2_free_dir_lookup_result(&orphan_insert);
	ocfs2_free_dir_lookup_result(&lookup);

	mlog_exit(status);

	return status;
}