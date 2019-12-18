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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {int /*<<< orphan*/ * d_op; TYPE_1__ d_name; struct inode* d_inode; } ;
struct TYPE_4__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit_ptr (struct dentry*) ; 
 int /*<<< orphan*/  ocfs2_dentry_ops ; 
 int /*<<< orphan*/  ocfs2_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_lookup_ino_from_name (struct inode*,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *ocfs2_get_parent(struct dentry *child)
{
	int status;
	u64 blkno;
	struct dentry *parent;
	struct inode *dir = child->d_inode;

	mlog_entry("(0x%p, '%.*s')\n", child,
		   child->d_name.len, child->d_name.name);

	mlog(0, "find parent of directory %llu\n",
	     (unsigned long long)OCFS2_I(dir)->ip_blkno);

	status = ocfs2_inode_lock(dir, NULL, 0);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		parent = ERR_PTR(status);
		goto bail;
	}

	status = ocfs2_lookup_ino_from_name(dir, "..", 2, &blkno);
	if (status < 0) {
		parent = ERR_PTR(-ENOENT);
		goto bail_unlock;
	}

	parent = d_obtain_alias(ocfs2_iget(OCFS2_SB(dir->i_sb), blkno, 0, 0));
	if (!IS_ERR(parent))
		parent->d_op = &ocfs2_dentry_ops;

bail_unlock:
	ocfs2_inode_unlock(dir, 0);

bail:
	mlog_exit_ptr(parent);

	return parent;
}