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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_inode_info {scalar_t__ ip_blkno; int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_flags; } ;
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/ * d_op; TYPE_1__ d_name; } ;

/* Variables and functions */
 int EACCES ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INODE_MAYBE_ORPHANED ; 
 scalar_t__ OCFS2_MAX_FILENAME_LEN ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OI_LS_PARENT ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct inode*,struct dentry*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit_ptr (struct dentry*) ; 
 int ocfs2_dentry_attach_lock (struct dentry*,struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_dentry_ops ; 
 struct inode* ocfs2_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock_nested (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_lookup_ino_from_name (struct inode*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *ocfs2_lookup(struct inode *dir, struct dentry *dentry,
				   struct nameidata *nd)
{
	int status;
	u64 blkno;
	struct inode *inode = NULL;
	struct dentry *ret;
	struct ocfs2_inode_info *oi;

	mlog_entry("(0x%p, 0x%p, '%.*s')\n", dir, dentry,
		   dentry->d_name.len, dentry->d_name.name);

	if (dentry->d_name.len > OCFS2_MAX_FILENAME_LEN) {
		ret = ERR_PTR(-ENAMETOOLONG);
		goto bail;
	}

	mlog(0, "find name %.*s in directory %llu\n", dentry->d_name.len,
	     dentry->d_name.name, (unsigned long long)OCFS2_I(dir)->ip_blkno);

	status = ocfs2_inode_lock_nested(dir, NULL, 0, OI_LS_PARENT);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		ret = ERR_PTR(status);
		goto bail;
	}

	status = ocfs2_lookup_ino_from_name(dir, dentry->d_name.name,
					    dentry->d_name.len, &blkno);
	if (status < 0)
		goto bail_add;

	inode = ocfs2_iget(OCFS2_SB(dir->i_sb), blkno, 0, 0);
	if (IS_ERR(inode)) {
		ret = ERR_PTR(-EACCES);
		goto bail_unlock;
	}

	oi = OCFS2_I(inode);
	/* Clear any orphaned state... If we were able to look up the
	 * inode from a directory, it certainly can't be orphaned. We
	 * might have the bad state from a node which intended to
	 * orphan this inode but crashed before it could commit the
	 * unlink. */
	spin_lock(&oi->ip_lock);
	oi->ip_flags &= ~OCFS2_INODE_MAYBE_ORPHANED;
	spin_unlock(&oi->ip_lock);

bail_add:
	dentry->d_op = &ocfs2_dentry_ops;
	ret = d_splice_alias(inode, dentry);

	if (inode) {
		/*
		 * If d_splice_alias() finds a DCACHE_DISCONNECTED
		 * dentry, it will d_move() it on top of ourse. The
		 * return value will indicate this however, so in
		 * those cases, we switch them around for the locking
		 * code.
		 *
		 * NOTE: This dentry already has ->d_op set from
		 * ocfs2_get_parent() and ocfs2_get_dentry()
		 */
		if (ret)
			dentry = ret;

		status = ocfs2_dentry_attach_lock(dentry, inode,
						  OCFS2_I(dir)->ip_blkno);
		if (status) {
			mlog_errno(status);
			ret = ERR_PTR(status);
			goto bail_unlock;
		}
	}

bail_unlock:
	/* Don't drop the cluster lock until *after* the d_add --
	 * unlink on another node will message us to remove that
	 * dentry under this lock so otherwise we can race this with
	 * the downconvert thread and have a stale dentry. */
	ocfs2_inode_unlock(dir, 0);

bail:

	mlog_exit_ptr(ret);

	return ret;
}