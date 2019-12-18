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
struct inode {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  IS_POSIXACL (struct inode*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int btrfs_set_acl (int /*<<< orphan*/ *,struct inode*,struct posix_acl*,int) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 
 struct posix_acl* posix_acl_from_xattr (void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_valid (struct posix_acl*) ; 

__attribute__((used)) static int btrfs_xattr_set_acl(struct inode *inode, int type,
			       const void *value, size_t size)
{
	int ret;
	struct posix_acl *acl = NULL;

	if (!is_owner_or_cap(inode))
		return -EPERM;

	if (!IS_POSIXACL(inode))
		return -EOPNOTSUPP;

	if (value) {
		acl = posix_acl_from_xattr(value, size);
		if (IS_ERR(acl))
			return PTR_ERR(acl);

		if (acl) {
			ret = posix_acl_valid(acl);
			if (ret)
				goto out;
		}
	}

	ret = btrfs_set_acl(NULL, inode, acl, type);
out:
	posix_acl_release(acl);

	return ret;
}