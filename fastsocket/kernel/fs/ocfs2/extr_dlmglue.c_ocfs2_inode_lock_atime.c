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
struct vfsmount {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_should_update_atime (struct inode*,struct vfsmount*) ; 
 int /*<<< orphan*/  ocfs2_update_inode_atime (struct inode*,struct buffer_head*) ; 

int ocfs2_inode_lock_atime(struct inode *inode,
			  struct vfsmount *vfsmnt,
			  int *level)
{
	int ret;

	mlog_entry_void();
	ret = ocfs2_inode_lock(inode, NULL, 0);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	/*
	 * If we should update atime, we will get EX lock,
	 * otherwise we just get PR lock.
	 */
	if (ocfs2_should_update_atime(inode, vfsmnt)) {
		struct buffer_head *bh = NULL;

		ocfs2_inode_unlock(inode, 0);
		ret = ocfs2_inode_lock(inode, &bh, 1);
		if (ret < 0) {
			mlog_errno(ret);
			return ret;
		}
		*level = 1;
		if (ocfs2_should_update_atime(inode, vfsmnt))
			ocfs2_update_inode_atime(inode, bh);
		if (bh)
			brelse(bh);
	} else
		*level = 0;

	mlog_exit(ret);
	return ret;
}