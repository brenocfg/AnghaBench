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
typedef  int /*<<< orphan*/  tid_t ;
struct jfs_inode_info {int /*<<< orphan*/  commit_mutex; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 int __jfs_setxattr (int /*<<< orphan*/ ,struct inode*,char const*,void const*,size_t,int) ; 
 int can_set_xattr (struct inode*,char const*,void const*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 

int jfs_setxattr(struct dentry *dentry, const char *name, const void *value,
		 size_t value_len, int flags)
{
	struct inode *inode = dentry->d_inode;
	struct jfs_inode_info *ji = JFS_IP(inode);
	int rc;
	tid_t tid;

	if ((rc = can_set_xattr(inode, name, value, value_len)))
		return rc;

	if (value == NULL) {	/* empty EA, do not remove */
		value = "";
		value_len = 0;
	}

	tid = txBegin(inode->i_sb, 0);
	mutex_lock(&ji->commit_mutex);
	rc = __jfs_setxattr(tid, dentry->d_inode, name, value, value_len,
			    flags);
	if (!rc)
		rc = txCommit(tid, 1, &inode, 0);
	txEnd(tid);
	mutex_unlock(&ji->commit_mutex);

	return rc;
}