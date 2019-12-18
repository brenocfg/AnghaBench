#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {TYPE_3__* sb; } ;
struct ocfs2_security_xattr_info {int enable; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct ocfs2_dir_lookup_result {int /*<<< orphan*/ * member_0; } ;
struct ocfs2_dinode {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {scalar_t__ i_nlink; int i_mode; int /*<<< orphan*/  i_sb; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {int /*<<< orphan*/ * d_op; TYPE_2__ d_name; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ dev_t ;
struct TYPE_9__ {int /*<<< orphan*/  ip_blkno; } ;
struct TYPE_8__ {TYPE_1__* dq_op; } ;
struct TYPE_6__ {scalar_t__ (* alloc_inode ) (struct inode*,int) ;} ;

/* Variables and functions */
 int EDQUOT ; 
 int EMLINK ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ NO_QUOTA ; 
 TYPE_5__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ S_ISDIR (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct inode*,struct dentry*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_add_entry (int /*<<< orphan*/ *,struct dentry*,struct inode*,int /*<<< orphan*/ ,struct buffer_head*,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_add_links_count (struct ocfs2_dinode*,int) ; 
 int ocfs2_calc_xattr_init (struct inode*,struct buffer_head*,int,struct ocfs2_security_xattr_info*,int*,int*,int*) ; 
 int ocfs2_check_dir_for_entry (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_dentry_attach_lock (struct dentry*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_dentry_ops ; 
 int ocfs2_fill_new_dir (struct ocfs2_super*,int /*<<< orphan*/ *,struct inode*,struct inode*,struct buffer_head*,struct ocfs2_alloc_context*,struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_free_dir_lookup_result (struct ocfs2_dir_lookup_result*) ; 
 struct inode* ocfs2_get_init_inode (struct inode*,int) ; 
 int ocfs2_init_acl (int /*<<< orphan*/ *,struct inode*,struct inode*,struct buffer_head*,struct buffer_head*,struct ocfs2_alloc_context*,struct ocfs2_alloc_context*) ; 
 int ocfs2_init_security_get (struct inode*,struct inode*,struct ocfs2_security_xattr_info*) ; 
 int ocfs2_init_security_set (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,struct ocfs2_security_xattr_info*,struct ocfs2_alloc_context*,struct ocfs2_alloc_context*) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 scalar_t__ ocfs2_link_max (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_mknod_credits (TYPE_3__*,scalar_t__,int) ; 
 int ocfs2_mknod_locked (struct ocfs2_super*,struct inode*,struct inode*,scalar_t__,struct buffer_head**,struct buffer_head*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*) ; 
 int ocfs2_prepare_dir_for_insert (struct ocfs2_super*,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_read_links_count (struct ocfs2_dinode*) ; 
 int ocfs2_reserve_clusters (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int ocfs2_reserve_new_inode (struct ocfs2_super*,struct ocfs2_alloc_context**) ; 
 int ocfs2_reserve_new_metadata_blocks (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_supports_indexed_dirs (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_supports_inline_data (struct ocfs2_super*) ; 
 scalar_t__ sb_any_quota_active (TYPE_3__*) ; 
 scalar_t__ stub1 (struct inode*,int) ; 
 int /*<<< orphan*/  vfs_dq_free_inode (struct inode*) ; 

__attribute__((used)) static int ocfs2_mknod(struct inode *dir,
		       struct dentry *dentry,
		       int mode,
		       dev_t dev)
{
	int status = 0;
	struct buffer_head *parent_fe_bh = NULL;
	handle_t *handle = NULL;
	struct ocfs2_super *osb;
	struct ocfs2_dinode *dirfe;
	struct buffer_head *new_fe_bh = NULL;
	struct inode *inode = NULL;
	struct ocfs2_alloc_context *inode_ac = NULL;
	struct ocfs2_alloc_context *data_ac = NULL;
	struct ocfs2_alloc_context *meta_ac = NULL;
	int want_clusters = 0;
	int want_meta = 0;
	int xattr_credits = 0;
	struct ocfs2_security_xattr_info si = {
		.enable = 1,
	};
	int did_quota_inode = 0;
	struct ocfs2_dir_lookup_result lookup = { NULL, };

	mlog_entry("(0x%p, 0x%p, %d, %lu, '%.*s')\n", dir, dentry, mode,
		   (unsigned long)dev, dentry->d_name.len,
		   dentry->d_name.name);

	/* get our super block */
	osb = OCFS2_SB(dir->i_sb);

	status = ocfs2_inode_lock(dir, &parent_fe_bh, 1);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		return status;
	}

	if (S_ISDIR(mode) && (dir->i_nlink >= ocfs2_link_max(osb))) {
		status = -EMLINK;
		goto leave;
	}

	dirfe = (struct ocfs2_dinode *) parent_fe_bh->b_data;
	if (!ocfs2_read_links_count(dirfe)) {
		/* can't make a file in a deleted directory. */
		status = -ENOENT;
		goto leave;
	}

	status = ocfs2_check_dir_for_entry(dir, dentry->d_name.name,
					   dentry->d_name.len);
	if (status)
		goto leave;

	/* get a spot inside the dir. */
	status = ocfs2_prepare_dir_for_insert(osb, dir, parent_fe_bh,
					      dentry->d_name.name,
					      dentry->d_name.len, &lookup);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	/* reserve an inode spot */
	status = ocfs2_reserve_new_inode(osb, &inode_ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto leave;
	}

	inode = ocfs2_get_init_inode(dir, mode);
	if (!inode) {
		status = -ENOMEM;
		mlog_errno(status);
		goto leave;
	}

	/* get security xattr */
	status = ocfs2_init_security_get(inode, dir, &si);
	if (status) {
		if (status == -EOPNOTSUPP)
			si.enable = 0;
		else {
			mlog_errno(status);
			goto leave;
		}
	}

	/* calculate meta data/clusters for setting security and acl xattr */
	status = ocfs2_calc_xattr_init(dir, parent_fe_bh, mode,
				       &si, &want_clusters,
				       &xattr_credits, &want_meta);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	/* Reserve a cluster if creating an extent based directory. */
	if (S_ISDIR(mode) && !ocfs2_supports_inline_data(osb)) {
		want_clusters += 1;

		/* Dir indexing requires extra space as well */
		if (ocfs2_supports_indexed_dirs(osb))
			want_meta++;
	}

	status = ocfs2_reserve_new_metadata_blocks(osb, want_meta, &meta_ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto leave;
	}

	status = ocfs2_reserve_clusters(osb, want_clusters, &data_ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto leave;
	}

	handle = ocfs2_start_trans(osb, ocfs2_mknod_credits(osb->sb,
							    S_ISDIR(mode),
							    xattr_credits));
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto leave;
	}

	/* We don't use standard VFS wrapper because we don't want vfs_dq_init
	 * to be called. */
	if (sb_any_quota_active(osb->sb) &&
	    osb->sb->dq_op->alloc_inode(inode, 1) == NO_QUOTA) {
		status = -EDQUOT;
		goto leave;
	}
	did_quota_inode = 1;

	mlog_entry("(0x%p, 0x%p, %d, %lu, '%.*s')\n", dir, dentry,
		   inode->i_mode, (unsigned long)dev, dentry->d_name.len,
		   dentry->d_name.name);

	/* do the real work now. */
	status = ocfs2_mknod_locked(osb, dir, inode, dev,
				    &new_fe_bh, parent_fe_bh, handle,
				    inode_ac);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	if (S_ISDIR(mode)) {
		status = ocfs2_fill_new_dir(osb, handle, dir, inode,
					    new_fe_bh, data_ac, meta_ac);
		if (status < 0) {
			mlog_errno(status);
			goto leave;
		}

		status = ocfs2_journal_access_di(handle, INODE_CACHE(dir),
						 parent_fe_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		if (status < 0) {
			mlog_errno(status);
			goto leave;
		}
		ocfs2_add_links_count(dirfe, 1);
		status = ocfs2_journal_dirty(handle, parent_fe_bh);
		if (status < 0) {
			mlog_errno(status);
			goto leave;
		}
		inc_nlink(dir);
	}

	status = ocfs2_init_acl(handle, inode, dir, new_fe_bh, parent_fe_bh,
				meta_ac, data_ac);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	if (si.enable) {
		status = ocfs2_init_security_set(handle, inode, new_fe_bh, &si,
						 meta_ac, data_ac);
		if (status < 0) {
			mlog_errno(status);
			goto leave;
		}
	}

	status = ocfs2_add_entry(handle, dentry, inode,
				 OCFS2_I(inode)->ip_blkno, parent_fe_bh,
				 &lookup);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	status = ocfs2_dentry_attach_lock(dentry, inode,
					  OCFS2_I(dir)->ip_blkno);
	if (status) {
		mlog_errno(status);
		goto leave;
	}

	insert_inode_hash(inode);
	dentry->d_op = &ocfs2_dentry_ops;
	d_instantiate(dentry, inode);
	status = 0;
leave:
	if (status < 0 && did_quota_inode)
		vfs_dq_free_inode(inode);
	if (handle)
		ocfs2_commit_trans(osb, handle);

	ocfs2_inode_unlock(dir, 1);

	if (status == -ENOSPC)
		mlog(0, "Disk is full\n");

	brelse(new_fe_bh);
	brelse(parent_fe_bh);
	kfree(si.name);
	kfree(si.value);

	ocfs2_free_dir_lookup_result(&lookup);

	if ((status < 0) && inode) {
		clear_nlink(inode);
		iput(inode);
	}

	if (inode_ac)
		ocfs2_free_alloc_context(inode_ac);

	if (data_ac)
		ocfs2_free_alloc_context(data_ac);

	if (meta_ac)
		ocfs2_free_alloc_context(meta_ac);

	mlog_exit(status);

	return status;
}