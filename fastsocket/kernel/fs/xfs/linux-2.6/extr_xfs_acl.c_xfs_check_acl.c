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
struct xfs_inode {int dummy; } ;
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 int /*<<< orphan*/  XFS_IFORK_Q (struct xfs_inode*) ; 
 int posix_acl_permission (struct inode*,struct posix_acl*,int) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int /*<<< orphan*/  trace_xfs_check_acl (struct xfs_inode*) ; 
 struct posix_acl* xfs_get_acl (struct inode*,int /*<<< orphan*/ ) ; 

int
xfs_check_acl(struct inode *inode, int mask)
{
	struct xfs_inode *ip = XFS_I(inode);
	struct posix_acl *acl;
	int error = -EAGAIN;

	trace_xfs_check_acl(ip);

	/*
	 * If there is no attribute fork no ACL exists on this inode and
	 * we can skip the whole exercise.
	 */
	if (!XFS_IFORK_Q(ip))
		return -EAGAIN;

	acl = xfs_get_acl(inode, ACL_TYPE_ACCESS);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	if (acl) {
		error = posix_acl_permission(inode, acl, mask);
		posix_acl_release(acl);
	}

	return error;
}