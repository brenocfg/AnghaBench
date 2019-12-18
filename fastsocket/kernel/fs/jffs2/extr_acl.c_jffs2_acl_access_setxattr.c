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

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int EINVAL ; 
 int jffs2_acl_setxattr (struct inode*,int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int jffs2_acl_access_setxattr(struct inode *inode, const char *name,
				     const void *buffer, size_t size, int flags)
{
	if (name[0] != '\0')
		return -EINVAL;
	return jffs2_acl_setxattr(inode, ACL_TYPE_ACCESS, buffer, size);
}