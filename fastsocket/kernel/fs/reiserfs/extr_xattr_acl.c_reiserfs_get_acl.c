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
 int ENODATA ; 
 int ENOMEM ; 
 int ENOSYS ; 
 struct posix_acl* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IS_ERR (struct posix_acl*) ; 
 char* POSIX_ACL_XATTR_ACCESS ; 
 char* POSIX_ACL_XATTR_DEFAULT ; 
 struct posix_acl* get_cached_acl (struct inode*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_from_disk (char*,int) ; 
 int reiserfs_xattr_get (struct inode*,char*,char*,int) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

struct posix_acl *reiserfs_get_acl(struct inode *inode, int type)
{
	char *name, *value;
	struct posix_acl *acl;
	int size;
	int retval;

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

	size = reiserfs_xattr_get(inode, name, NULL, 0);
	if (size < 0) {
		if (size == -ENODATA || size == -ENOSYS) {
			set_cached_acl(inode, type, NULL);
			return NULL;
		}
		return ERR_PTR(size);
	}

	value = kmalloc(size, GFP_NOFS);
	if (!value)
		return ERR_PTR(-ENOMEM);

	retval = reiserfs_xattr_get(inode, name, value, size);
	if (retval == -ENODATA || retval == -ENOSYS) {
		/* This shouldn't actually happen as it should have
		   been caught above.. but just in case */
		acl = NULL;
	} else if (retval < 0) {
		acl = ERR_PTR(retval);
	} else {
		acl = posix_acl_from_disk(value, retval);
	}
	if (!IS_ERR(acl))
		set_cached_acl(inode, type, acl);

	kfree(value);
	return acl;
}