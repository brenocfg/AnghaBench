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
struct posix_acl {int dummy; } ;
struct ocfs2_super {int s_mount_opt; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 struct posix_acl* ERR_PTR (int) ; 
 int OCFS2_MOUNT_POSIX_ACL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct posix_acl* ocfs2_get_acl_nolock (struct inode*,int,struct buffer_head*) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct posix_acl *ocfs2_get_acl(struct inode *inode, int type)
{
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct buffer_head *di_bh = NULL;
	struct posix_acl *acl;
	int ret;

	if (!(osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL))
		return NULL;

	ret = ocfs2_inode_lock(inode, &di_bh, 0);
	if (ret < 0) {
		mlog_errno(ret);
		acl = ERR_PTR(ret);
		return acl;
	}

	acl = ocfs2_get_acl_nolock(inode, type, di_bh);

	ocfs2_inode_unlock(inode, 0);

	brelse(di_bh);

	return acl;
}