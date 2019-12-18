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
struct dentry {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SETFCAP ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 int /*<<< orphan*/  FILE__SETATTR ; 
 int /*<<< orphan*/  XATTR_NAME_CAPS ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 int dentry_has_perm (struct cred const*,int /*<<< orphan*/ *,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int selinux_inode_setotherxattr(struct dentry *dentry, const char *name)
{
	const struct cred *cred = current_cred();

	if (!strncmp(name, XATTR_SECURITY_PREFIX,
		     sizeof XATTR_SECURITY_PREFIX - 1)) {
		if (!strcmp(name, XATTR_NAME_CAPS)) {
			if (!capable(CAP_SETFCAP))
				return -EPERM;
		} else if (!capable(CAP_SYS_ADMIN)) {
			/* A different attribute in the security namespace.
			   Restrict to administrator. */
			return -EPERM;
		}
	}

	/* Not an attribute we recognize, so just check the
	   ordinary setattr permission. */
	return dentry_has_perm(cred, NULL, dentry, FILE__SETATTR);
}