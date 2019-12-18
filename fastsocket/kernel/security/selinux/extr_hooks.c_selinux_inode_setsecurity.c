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
typedef  int /*<<< orphan*/  u32 ;
struct inode_security_struct {int initialized; int /*<<< orphan*/  sid; } ;
struct inode {struct inode_security_struct* i_security; } ;

/* Variables and functions */
 int EACCES ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  XATTR_SELINUX_SUFFIX ; 
 int security_context_to_sid (void*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_inode_setsecurity(struct inode *inode, const char *name,
				     const void *value, size_t size, int flags)
{
	struct inode_security_struct *isec = inode->i_security;
	u32 newsid;
	int rc;

	if (strcmp(name, XATTR_SELINUX_SUFFIX))
		return -EOPNOTSUPP;

	if (!value || !size)
		return -EACCES;

	rc = security_context_to_sid((void *)value, size, &newsid);
	if (rc)
		return rc;

	isec->sid = newsid;
	isec->initialized = 1;
	return 0;
}