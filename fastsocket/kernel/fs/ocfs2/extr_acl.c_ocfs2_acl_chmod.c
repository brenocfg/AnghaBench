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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int OCFS2_MOUNT_POSIX_ACL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct posix_acl*) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 struct posix_acl* ocfs2_get_acl (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_set_acl (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct posix_acl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int posix_acl_chmod_masq (struct posix_acl*,int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_clone (struct posix_acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

int ocfs2_acl_chmod(struct inode *inode)
{
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct posix_acl *acl, *clone;
	int ret;

	if (S_ISLNK(inode->i_mode))
		return -EOPNOTSUPP;

	if (!(osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL))
		return 0;

	acl = ocfs2_get_acl(inode, ACL_TYPE_ACCESS);
	if (IS_ERR(acl) || !acl)
		return PTR_ERR(acl);
	clone = posix_acl_clone(acl, GFP_KERNEL);
	posix_acl_release(acl);
	if (!clone)
		return -ENOMEM;
	ret = posix_acl_chmod_masq(clone, inode->i_mode);
	if (!ret)
		ret = ocfs2_set_acl(NULL, inode, NULL, ACL_TYPE_ACCESS,
				    clone, NULL, NULL);
	posix_acl_release(clone);
	return ret;
}