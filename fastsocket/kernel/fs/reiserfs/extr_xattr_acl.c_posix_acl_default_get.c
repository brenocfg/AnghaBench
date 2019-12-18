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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  POSIX_ACL_XATTR_DEFAULT ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int EINVAL ; 
 int strlen (char const*) ; 
 int xattr_get_acl (struct inode*,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int
posix_acl_default_get(struct inode *inode, const char *name,
		      void *buffer, size_t size)
{
	if (strlen(name) != sizeof(POSIX_ACL_XATTR_DEFAULT) - 1)
		return -EINVAL;
	return xattr_get_acl(inode, ACL_TYPE_DEFAULT, buffer, size);
}