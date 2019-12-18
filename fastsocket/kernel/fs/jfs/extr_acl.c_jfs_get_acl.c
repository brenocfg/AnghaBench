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
 int EINVAL ; 
 int ENODATA ; 
 int ENOMEM ; 
 struct posix_acl* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct posix_acl*) ; 
 char* POSIX_ACL_XATTR_ACCESS ; 
 char* POSIX_ACL_XATTR_DEFAULT ; 
 int __jfs_getxattr (struct inode*,char*,char*,int) ; 
 struct posix_acl* get_cached_acl (struct inode*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_from_xattr (char*,int) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

__attribute__((used)) static struct posix_acl *jfs_get_acl(struct inode *inode, int type)
{
	struct posix_acl *acl;
	char *ea_name;
	int size;
	char *value = NULL;

	acl = get_cached_acl(inode, type);
	if (acl != ACL_NOT_CACHED)
		return acl;

	switch(type) {
		case ACL_TYPE_ACCESS:
			ea_name = POSIX_ACL_XATTR_ACCESS;
			break;
		case ACL_TYPE_DEFAULT:
			ea_name = POSIX_ACL_XATTR_DEFAULT;
			break;
		default:
			return ERR_PTR(-EINVAL);
	}

	size = __jfs_getxattr(inode, ea_name, NULL, 0);

	if (size > 0) {
		value = kmalloc(size, GFP_KERNEL);
		if (!value)
			return ERR_PTR(-ENOMEM);
		size = __jfs_getxattr(inode, ea_name, value, size);
	}

	if (size < 0) {
		if (size == -ENODATA)
			acl = NULL;
		else
			acl = ERR_PTR(size);
	} else {
		acl = posix_acl_from_xattr(value, size);
	}
	kfree(value);
	if (!IS_ERR(acl))
		set_cached_acl(inode, type, acl);
	return acl;
}