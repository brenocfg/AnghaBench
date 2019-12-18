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
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int generic_permission (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_check_acl ; 
 int ocfs2_inode_lock (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 

int ocfs2_permission(struct inode *inode, int mask)
{
	int ret;

	mlog_entry_void();

	ret = ocfs2_inode_lock(inode, NULL, 0);
	if (ret) {
		if (ret != -ENOENT)
			mlog_errno(ret);
		goto out;
	}

	ret = generic_permission(inode, mask, ocfs2_check_acl);

	ocfs2_inode_unlock(inode, 0);
out:
	mlog_exit(ret);
	return ret;
}