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
struct iattr {int /*<<< orphan*/  ia_mode; int /*<<< orphan*/  ia_valid; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int /*<<< orphan*/  ATTR_MODE ; 
 int EACCES ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int JFFS2_XPREFIX_ACL_ACCESS ; 
 int JFFS2_XPREFIX_ACL_DEFAULT ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int __jffs2_set_acl (struct inode*,int,struct posix_acl*) ; 
 int jffs2_do_setattr (struct inode*,struct iattr*) ; 
 int posix_acl_equiv_mode (struct posix_acl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

__attribute__((used)) static int jffs2_set_acl(struct inode *inode, int type, struct posix_acl *acl)
{
	int rc, xprefix;

	if (S_ISLNK(inode->i_mode))
		return -EOPNOTSUPP;

	switch (type) {
	case ACL_TYPE_ACCESS:
		xprefix = JFFS2_XPREFIX_ACL_ACCESS;
		if (acl) {
			mode_t mode = inode->i_mode;
			rc = posix_acl_equiv_mode(acl, &mode);
			if (rc < 0)
				return rc;
			if (inode->i_mode != mode) {
				struct iattr attr;

				attr.ia_valid = ATTR_MODE;
				attr.ia_mode = mode;
				rc = jffs2_do_setattr(inode, &attr);
				if (rc < 0)
					return rc;
			}
			if (rc == 0)
				acl = NULL;
		}
		break;
	case ACL_TYPE_DEFAULT:
		xprefix = JFFS2_XPREFIX_ACL_DEFAULT;
		if (!S_ISDIR(inode->i_mode))
			return acl ? -EACCES : 0;
		break;
	default:
		return -EINVAL;
	}
	rc = __jffs2_set_acl(inode, xprefix, acl);
	if (!rc)
		set_cached_acl(inode, type, acl);
	return rc;
}