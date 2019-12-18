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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_clone (struct posix_acl*,int /*<<< orphan*/ ) ; 
 int posix_acl_create_masq (struct posix_acl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int xfs_set_acl (struct inode*,int /*<<< orphan*/ ,struct posix_acl*) ; 
 int xfs_set_mode (struct inode*,int /*<<< orphan*/ ) ; 

int
xfs_inherit_acl(struct inode *inode, struct posix_acl *default_acl)
{
	struct posix_acl *clone;
	mode_t mode;
	int error = 0, inherit = 0;

	if (S_ISDIR(inode->i_mode)) {
		error = xfs_set_acl(inode, ACL_TYPE_DEFAULT, default_acl);
		if (error)
			return error;
	}

	clone = posix_acl_clone(default_acl, GFP_KERNEL);
	if (!clone)
		return -ENOMEM;

	mode = inode->i_mode;
	error = posix_acl_create_masq(clone, &mode);
	if (error < 0)
		goto out_release_clone;

	/*
	 * If posix_acl_create_masq returns a positive value we need to
	 * inherit a permission that can't be represented using the Unix
	 * mode bits and we actually need to set an ACL.
	 */
	if (error > 0)
		inherit = 1;

	error = xfs_set_mode(inode, mode);
	if (error)
		goto out_release_clone;

	if (inherit)
		error = xfs_set_acl(inode, ACL_TYPE_ACCESS, clone);

 out_release_clone:
	posix_acl_release(clone);
	return error;
}