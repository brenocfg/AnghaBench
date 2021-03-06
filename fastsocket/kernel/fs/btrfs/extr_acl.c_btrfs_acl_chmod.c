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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (struct posix_acl*) ; 
 int /*<<< orphan*/  IS_POSIXACL (struct inode*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 struct posix_acl* btrfs_get_acl (struct inode*,int /*<<< orphan*/ ) ; 
 int btrfs_set_acl (int /*<<< orphan*/ *,struct inode*,struct posix_acl*,int /*<<< orphan*/ ) ; 
 int posix_acl_chmod_masq (struct posix_acl*,int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_clone (struct posix_acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

int btrfs_acl_chmod(struct inode *inode)
{
	struct posix_acl *acl, *clone;
	int ret = 0;

	if (S_ISLNK(inode->i_mode))
		return -EOPNOTSUPP;

	if (!IS_POSIXACL(inode))
		return 0;

	acl = btrfs_get_acl(inode, ACL_TYPE_ACCESS);
	if (IS_ERR_OR_NULL(acl))
		return PTR_ERR(acl);

	clone = posix_acl_clone(acl, GFP_KERNEL);
	posix_acl_release(acl);
	if (!clone)
		return -ENOMEM;

	ret = posix_acl_chmod_masq(clone, inode->i_mode);
	if (!ret)
		ret = btrfs_set_acl(NULL, inode, clone, ACL_TYPE_ACCESS);

	posix_acl_release(clone);

	return ret;
}