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
struct posix_acl {int /*<<< orphan*/  a_count; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct btrfs_trans_handle {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 char* POSIX_ACL_XATTR_ACCESS ; 
 char* POSIX_ACL_XATTR_DEFAULT ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int __btrfs_setxattr (struct btrfs_trans_handle*,struct inode*,char const*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int posix_acl_equiv_mode (struct posix_acl*,int /*<<< orphan*/ *) ; 
 int posix_acl_to_xattr (struct posix_acl*,char*,int) ; 
 int posix_acl_valid (struct posix_acl*) ; 
 int posix_acl_xattr_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

__attribute__((used)) static int btrfs_set_acl(struct btrfs_trans_handle *trans,
			 struct inode *inode, struct posix_acl *acl, int type)
{
	int ret, size = 0;
	const char *name;
	char *value = NULL;
	mode_t mode;

	if (acl) {
		ret = posix_acl_valid(acl);
		if (ret < 0)
			return ret;
		ret = 0;
	}

	switch (type) {
	case ACL_TYPE_ACCESS:
		mode = inode->i_mode;
		name = POSIX_ACL_XATTR_ACCESS;
		if (acl) {
			ret = posix_acl_equiv_mode(acl, &mode);
			if (ret < 0)
				return ret;
			inode->i_mode = mode;
		}
		ret = 0;
		break;
	case ACL_TYPE_DEFAULT:
		if (!S_ISDIR(inode->i_mode))
			return acl ? -EINVAL : 0;
		name = POSIX_ACL_XATTR_DEFAULT;
		break;
	default:
		return -EINVAL;
	}

	if (acl) {
		size = posix_acl_xattr_size(acl->a_count);
		value = kmalloc(size, GFP_NOFS);
		if (!value) {
			ret = -ENOMEM;
			goto out;
		}

		ret = posix_acl_to_xattr(acl, value, size);
		if (ret < 0)
			goto out;
	}

	ret = __btrfs_setxattr(trans, inode, name, value, size, 0);
out:
	kfree(value);

	if (!ret)
		set_cached_acl(inode, type, acl);

	return ret;
}