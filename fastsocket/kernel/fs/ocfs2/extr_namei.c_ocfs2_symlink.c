#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct ocfs2_super {TYPE_4__* sb; } ;
struct ocfs2_security_xattr_info {int enable; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct ocfs2_dir_lookup_result {int /*<<< orphan*/ * member_0; } ;
struct TYPE_7__ {scalar_t__ i_symlink; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_blkno; TYPE_1__ id2; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {char const* i_mode; scalar_t__ i_blocks; int /*<<< orphan*/ * i_op; scalar_t__ i_rdev; struct super_block* i_sb; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {int /*<<< orphan*/ * d_op; TYPE_3__ d_name; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_11__ {int /*<<< orphan*/  ip_blkno; } ;
struct TYPE_10__ {TYPE_2__* dq_op; } ;
struct TYPE_8__ {scalar_t__ (* alloc_inode ) (struct inode*,int) ;} ;

/* Variables and functions */
 int EDQUOT ; 
 int EINTR ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ NO_QUOTA ; 
 TYPE_6__* OCFS2_I (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct inode*,struct dentry*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_add_entry (int /*<<< orphan*/ *,struct dentry*,struct inode*,int /*<<< orphan*/ ,struct buffer_head*,struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_add_inode_data (struct ocfs2_super*,struct inode*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ocfs2_calc_security_init (struct inode*,struct ocfs2_security_xattr_info*,int*,int*,struct ocfs2_alloc_context**) ; 
 int ocfs2_calc_symlink_credits (struct super_block*) ; 
 int ocfs2_check_dir_for_entry (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_bytes (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_create_symlink_data (struct ocfs2_super*,int /*<<< orphan*/ *,struct inode*,char const*) ; 
 int ocfs2_dentry_attach_lock (struct dentry*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_dentry_ops ; 
 int ocfs2_fast_symlink_chars (struct super_block*) ; 
 int /*<<< orphan*/  ocfs2_fast_symlink_inode_operations ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_free_dir_lookup_result (struct ocfs2_dir_lookup_result*) ; 
 struct inode* ocfs2_get_init_inode (struct inode*,int) ; 
 int ocfs2_init_security_get (struct inode*,struct inode*,struct ocfs2_security_xattr_info*) ; 
 int ocfs2_init_security_set (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,struct ocfs2_security_xattr_info*,struct ocfs2_alloc_context*,struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_inode_is_fast_symlink (struct inode*) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 scalar_t__ ocfs2_inode_sector_count (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int ocfs2_mknod_locked (struct ocfs2_super*,struct inode*,struct inode*,int /*<<< orphan*/ ,struct buffer_head**,struct buffer_head*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*) ; 
 int ocfs2_prepare_dir_for_insert (struct ocfs2_super*,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_read_links_count (struct ocfs2_dinode*) ; 
 int ocfs2_reserve_clusters (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int ocfs2_reserve_new_inode (struct ocfs2_super*,struct ocfs2_alloc_context**) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_symlink_inode_operations ; 
 scalar_t__ sb_any_quota_active (TYPE_4__*) ; 
 int strlen (char const*) ; 
 scalar_t__ stub1 (struct inode*,int) ; 
 scalar_t__ vfs_dq_alloc_space_nodirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_free_inode (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_free_space_nodirty (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_symlink(struct inode *dir,
			 struct dentry *dentry,
			 const char *symname)
{
	int status, l, credits;
	u64 newsize;
	struct ocfs2_super *osb = NULL;
	struct inode *inode = NULL;
	struct super_block *sb;
	struct buffer_head *new_fe_bh = NULL;
	struct buffer_head *parent_fe_bh = NULL;
	struct ocfs2_dinode *fe = NULL;
	struct ocfs2_dinode *dirfe;
	handle_t *handle = NULL;
	struct ocfs2_alloc_context *inode_ac = NULL;
	struct ocfs2_alloc_context *data_ac = NULL;
	struct ocfs2_alloc_context *xattr_ac = NULL;
	int want_clusters = 0;
	int xattr_credits = 0;
	struct ocfs2_security_xattr_info si = {
		.enable = 1,
	};
	int did_quota = 0, did_quota_inode = 0;
	struct ocfs2_dir_lookup_result lookup = { NULL, };

	mlog_entry("(0x%p, 0x%p, symname='%s' actual='%.*s')\n", dir,
		   dentry, symname, dentry->d_name.len, dentry->d_name.name);

	sb = dir->i_sb;
	osb = OCFS2_SB(sb);

	l = strlen(symname) + 1;

	credits = ocfs2_calc_symlink_credits(sb);

	/* lock the parent directory */
	status = ocfs2_inode_lock(dir, &parent_fe_bh, 1);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		return status;
	}

	dirfe = (struct ocfs2_dinode *) parent_fe_bh->b_data;
	if (!ocfs2_read_links_count(dirfe)) {
		/* can't make a file in a deleted directory. */
		status = -ENOENT;
		goto bail;
	}

	status = ocfs2_check_dir_for_entry(dir, dentry->d_name.name,
					   dentry->d_name.len);
	if (status)
		goto bail;

	status = ocfs2_prepare_dir_for_insert(osb, dir, parent_fe_bh,
					      dentry->d_name.name,
					      dentry->d_name.len, &lookup);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_reserve_new_inode(osb, &inode_ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	inode = ocfs2_get_init_inode(dir, S_IFLNK | S_IRWXUGO);
	if (!inode) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	/* get security xattr */
	status = ocfs2_init_security_get(inode, dir, &si);
	if (status) {
		if (status == -EOPNOTSUPP)
			si.enable = 0;
		else {
			mlog_errno(status);
			goto bail;
		}
	}

	/* calculate meta data/clusters for setting security xattr */
	if (si.enable) {
		status = ocfs2_calc_security_init(dir, &si, &want_clusters,
						  &xattr_credits, &xattr_ac);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	/* don't reserve bitmap space for fast symlinks. */
	if (l > ocfs2_fast_symlink_chars(sb))
		want_clusters += 1;

	status = ocfs2_reserve_clusters(osb, want_clusters, &data_ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	handle = ocfs2_start_trans(osb, credits + xattr_credits);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto bail;
	}

	/* We don't use standard VFS wrapper because we don't want vfs_dq_init
	 * to be called. */
	if (sb_any_quota_active(osb->sb) &&
	    osb->sb->dq_op->alloc_inode(inode, 1) == NO_QUOTA) {
		status = -EDQUOT;
		goto bail;
	}
	did_quota_inode = 1;

	mlog_entry("(0x%p, 0x%p, %d, '%.*s')\n", dir, dentry,
		   inode->i_mode, dentry->d_name.len,
		   dentry->d_name.name);

	status = ocfs2_mknod_locked(osb, dir, inode,
				    0, &new_fe_bh, parent_fe_bh, handle,
				    inode_ac);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	fe = (struct ocfs2_dinode *) new_fe_bh->b_data;
	inode->i_rdev = 0;
	newsize = l - 1;
	if (l > ocfs2_fast_symlink_chars(sb)) {
		u32 offset = 0;

		inode->i_op = &ocfs2_symlink_inode_operations;
		if (vfs_dq_alloc_space_nodirty(inode,
		    ocfs2_clusters_to_bytes(osb->sb, 1))) {
			status = -EDQUOT;
			goto bail;
		}
		did_quota = 1;
		status = ocfs2_add_inode_data(osb, inode, &offset, 1, 0,
					      new_fe_bh,
					      handle, data_ac, NULL,
					      NULL);
		if (status < 0) {
			if (status != -ENOSPC && status != -EINTR) {
				mlog(ML_ERROR,
				     "Failed to extend file to %llu\n",
				     (unsigned long long)newsize);
				mlog_errno(status);
				status = -ENOSPC;
			}
			goto bail;
		}
		i_size_write(inode, newsize);
		inode->i_blocks = ocfs2_inode_sector_count(inode);
	} else {
		inode->i_op = &ocfs2_fast_symlink_inode_operations;
		memcpy((char *) fe->id2.i_symlink, symname, l);
		i_size_write(inode, newsize);
		inode->i_blocks = 0;
	}

	status = ocfs2_mark_inode_dirty(handle, inode, new_fe_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	if (!ocfs2_inode_is_fast_symlink(inode)) {
		status = ocfs2_create_symlink_data(osb, handle, inode,
						   symname);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	if (si.enable) {
		status = ocfs2_init_security_set(handle, inode, new_fe_bh, &si,
						 xattr_ac, data_ac);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	status = ocfs2_add_entry(handle, dentry, inode,
				 le64_to_cpu(fe->i_blkno), parent_fe_bh,
				 &lookup);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_dentry_attach_lock(dentry, inode, OCFS2_I(dir)->ip_blkno);
	if (status) {
		mlog_errno(status);
		goto bail;
	}

	insert_inode_hash(inode);
	dentry->d_op = &ocfs2_dentry_ops;
	d_instantiate(dentry, inode);
bail:
	if (status < 0 && did_quota)
		vfs_dq_free_space_nodirty(inode,
					ocfs2_clusters_to_bytes(osb->sb, 1));
	if (status < 0 && did_quota_inode)
		vfs_dq_free_inode(inode);
	if (handle)
		ocfs2_commit_trans(osb, handle);

	ocfs2_inode_unlock(dir, 1);

	brelse(new_fe_bh);
	brelse(parent_fe_bh);
	kfree(si.name);
	kfree(si.value);
	ocfs2_free_dir_lookup_result(&lookup);
	if (inode_ac)
		ocfs2_free_alloc_context(inode_ac);
	if (data_ac)
		ocfs2_free_alloc_context(data_ac);
	if (xattr_ac)
		ocfs2_free_alloc_context(xattr_ac);
	if ((status < 0) && inode) {
		clear_nlink(inode);
		iput(inode);
	}

	mlog_exit(status);

	return status;
}