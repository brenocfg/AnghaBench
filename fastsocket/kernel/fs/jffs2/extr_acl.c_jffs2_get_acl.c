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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct posix_acl*) ; 
 int JFFS2_XPREFIX_ACL_ACCESS ; 
 int JFFS2_XPREFIX_ACL_DEFAULT ; 
 int do_jffs2_getxattr (struct inode*,int,char*,char*,int) ; 
 struct posix_acl* get_cached_acl (struct inode*,int) ; 
 struct posix_acl* jffs2_acl_from_medium (char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

__attribute__((used)) static struct posix_acl *jffs2_get_acl(struct inode *inode, int type)
{
	struct posix_acl *acl;
	char *value = NULL;
	int rc, xprefix;

	acl = get_cached_acl(inode, type);
	if (acl != ACL_NOT_CACHED)
		return acl;

	switch (type) {
	case ACL_TYPE_ACCESS:
		xprefix = JFFS2_XPREFIX_ACL_ACCESS;
		break;
	case ACL_TYPE_DEFAULT:
		xprefix = JFFS2_XPREFIX_ACL_DEFAULT;
		break;
	default:
		BUG();
	}
	rc = do_jffs2_getxattr(inode, xprefix, "", NULL, 0);
	if (rc > 0) {
		value = kmalloc(rc, GFP_KERNEL);
		if (!value)
			return ERR_PTR(-ENOMEM);
		rc = do_jffs2_getxattr(inode, xprefix, "", value, rc);
	}
	if (rc > 0) {
		acl = jffs2_acl_from_medium(value, rc);
	} else if (rc == -ENODATA || rc == -ENOSYS) {
		acl = NULL;
	} else {
		acl = ERR_PTR(rc);
	}
	if (value)
		kfree(value);
	if (!IS_ERR(acl))
		set_cached_acl(inode, type, acl);
	return acl;
}