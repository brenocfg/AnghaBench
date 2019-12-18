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

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  XATTR_NAME_SELINUX ; 
 int selinux_inode_setotherxattr (struct dentry*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_inode_removexattr(struct dentry *dentry, const char *name)
{
	if (strcmp(name, XATTR_NAME_SELINUX))
		return selinux_inode_setotherxattr(dentry, name);

	/* No one is allowed to remove a SELinux security label.
	   You can change the label, but all data must be labeled. */
	return -EACCES;
}