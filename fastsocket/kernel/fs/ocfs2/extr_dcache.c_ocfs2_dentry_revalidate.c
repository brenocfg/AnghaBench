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
struct ocfs2_super {struct inode* root_inode; } ;
struct nameidata {int dummy; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {int /*<<< orphan*/  d_fsdata; TYPE_1__ d_name; int /*<<< orphan*/  d_sb; struct inode* d_inode; } ;
struct TYPE_4__ {int ip_flags; scalar_t__ ip_blkno; int /*<<< orphan*/  ip_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_DELETED ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_dentry_revalidate(struct dentry *dentry,
				   struct nameidata *nd)
{
	struct inode *inode = dentry->d_inode;
	int ret = 0;    /* if all else fails, just return false */
	struct ocfs2_super *osb = OCFS2_SB(dentry->d_sb);

	mlog_entry("(0x%p, '%.*s')\n", dentry,
		   dentry->d_name.len, dentry->d_name.name);

	/* Never trust a negative dentry - force a new lookup. */
	if (inode == NULL) {
		mlog(0, "negative dentry: %.*s\n", dentry->d_name.len,
		     dentry->d_name.name);
		goto bail;
	}

	BUG_ON(!osb);

	if (inode == osb->root_inode || is_bad_inode(inode))
		goto bail;

	spin_lock(&OCFS2_I(inode)->ip_lock);
	/* did we or someone else delete this inode? */
	if (OCFS2_I(inode)->ip_flags & OCFS2_INODE_DELETED) {
		spin_unlock(&OCFS2_I(inode)->ip_lock);
		mlog(0, "inode (%llu) deleted, returning false\n",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno);
		goto bail;
	}
	spin_unlock(&OCFS2_I(inode)->ip_lock);

	/*
	 * We don't need a cluster lock to test this because once an
	 * inode nlink hits zero, it never goes back.
	 */
	if (inode->i_nlink == 0) {
		mlog(0, "Inode %llu orphaned, returning false "
		     "dir = %d\n",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno,
		     S_ISDIR(inode->i_mode));
		goto bail;
	}

	/*
	 * If the last lookup failed to create dentry lock, let us
	 * redo it.
	 */
	if (!dentry->d_fsdata) {
		mlog(0, "Inode %llu doesn't have dentry lock, "
		     "returning false\n",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno);
		goto bail;
	}

	ret = 1;

bail:
	mlog_exit(ret);

	return ret;
}