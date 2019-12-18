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
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct posix_acl* ACL_NOT_CACHED ; 
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int /*<<< orphan*/  BUG () ; 
 int ENODATA ; 
 int ENOMEM ; 
 int ENOSYS ; 
 struct posix_acl* ERR_PTR (int) ; 
 int EXT3_XATTR_INDEX_POSIX_ACL_ACCESS ; 
 int EXT3_XATTR_INDEX_POSIX_ACL_DEFAULT ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IS_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  POSIX_ACL ; 
 struct posix_acl* ext3_acl_from_disk (char*,int) ; 
 int ext3_xattr_get (struct inode*,int,char*,char*,int) ; 
 struct posix_acl* get_cached_acl (struct inode*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 
 int /*<<< orphan*/  test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct posix_acl *
ext3_get_acl(struct inode *inode, int type)
{
	int name_index;
	char *value = NULL;
	struct posix_acl *acl;
	int retval;

	if (!test_opt(inode->i_sb, POSIX_ACL))
		return NULL;

	acl = get_cached_acl(inode, type);
	if (acl != ACL_NOT_CACHED)
		return acl;

	switch (type) {
	case ACL_TYPE_ACCESS:
		name_index = EXT3_XATTR_INDEX_POSIX_ACL_ACCESS;
		break;
	case ACL_TYPE_DEFAULT:
		name_index = EXT3_XATTR_INDEX_POSIX_ACL_DEFAULT;
		break;
	default:
		BUG();
	}

	retval = ext3_xattr_get(inode, name_index, "", NULL, 0);
	if (retval > 0) {
		value = kmalloc(retval, GFP_NOFS);
		if (!value)
			return ERR_PTR(-ENOMEM);
		retval = ext3_xattr_get(inode, name_index, "", value, retval);
	}
	if (retval > 0)
		acl = ext3_acl_from_disk(value, retval);
	else if (retval == -ENODATA || retval == -ENOSYS)
		acl = NULL;
	else
		acl = ERR_PTR(retval);
	kfree(value);

	if (!IS_ERR(acl))
		set_cached_acl(inode, type, acl);

	return acl;
}