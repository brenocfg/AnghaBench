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
struct iattr {unsigned int ia_valid; } ;
struct dentry {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 unsigned int ATTR_ATIME_SET ; 
 unsigned int ATTR_FORCE ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_KILL_SGID ; 
 unsigned int ATTR_KILL_SUID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME_SET ; 
 unsigned int ATTR_TIMES_SET ; 
 unsigned int ATTR_UID ; 
 int /*<<< orphan*/  FILE__SETATTR ; 
 int /*<<< orphan*/  FILE__WRITE ; 
 struct cred* current_cred () ; 
 int dentry_has_perm (struct cred const*,int /*<<< orphan*/ *,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_inode_setattr(struct dentry *dentry, struct iattr *iattr)
{
	const struct cred *cred = current_cred();
	unsigned int ia_valid = iattr->ia_valid;

	/* ATTR_FORCE is just used for ATTR_KILL_S[UG]ID. */
	if (ia_valid & ATTR_FORCE) {
		ia_valid &= ~(ATTR_KILL_SUID | ATTR_KILL_SGID | ATTR_MODE |
			      ATTR_FORCE);
		if (!ia_valid)
			return 0;
	}

	if (ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID |
			ATTR_ATIME_SET | ATTR_MTIME_SET | ATTR_TIMES_SET))
		return dentry_has_perm(cred, NULL, dentry, FILE__SETATTR);

	return dentry_has_perm(cred, NULL, dentry, FILE__WRITE);
}