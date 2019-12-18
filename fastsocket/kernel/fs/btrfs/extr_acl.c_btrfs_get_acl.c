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
 struct posix_acl* ACL_NOT_CACHED ; 
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EIO ; 
 int ENODATA ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct posix_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IS_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  IS_POSIXACL (struct inode*) ; 
 char* POSIX_ACL_XATTR_ACCESS ; 
 char* POSIX_ACL_XATTR_DEFAULT ; 
 int __btrfs_getxattr (struct inode*,char const*,char*,int) ; 
 struct posix_acl* get_cached_acl (struct inode*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_from_xattr (char*,int) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

__attribute__((used)) static struct posix_acl *btrfs_get_acl(struct inode *inode, int type)
{
	int size;
	const char *name;
	char *value = NULL;
	struct posix_acl *acl;

	if (!IS_POSIXACL(inode))
		return NULL;

	acl = get_cached_acl(inode, type);
	if (acl != ACL_NOT_CACHED)
		return acl;

	switch (type) {
	case ACL_TYPE_ACCESS:
		name = POSIX_ACL_XATTR_ACCESS;
		break;
	case ACL_TYPE_DEFAULT:
		name = POSIX_ACL_XATTR_DEFAULT;
		break;
	default:
		BUG();
	}

	size = __btrfs_getxattr(inode, name, "", 0);
	if (size > 0) {
		value = kzalloc(size, GFP_NOFS);
		if (!value)
			return ERR_PTR(-ENOMEM);
		size = __btrfs_getxattr(inode, name, value, size);
	}
	if (size > 0) {
		acl = posix_acl_from_xattr(value, size);
	} else if (size == -ENOENT || size == -ENODATA || size == 0) {
		/* FIXME, who returns -ENOENT?  I think nobody */
		acl = NULL;
	} else {
		acl = ERR_PTR(-EIO);
	}
	kfree(value);

	if (!IS_ERR(acl))
		set_cached_acl(inode, type, acl);

	return acl;
}