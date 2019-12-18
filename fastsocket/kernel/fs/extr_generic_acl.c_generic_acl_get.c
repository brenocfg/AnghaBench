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
struct generic_acl_operations {struct posix_acl* (* getacl ) (struct inode*,int) ;} ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_to_xattr (struct posix_acl*,void*,size_t) ; 
 struct posix_acl* stub1 (struct inode*,int) ; 

int
generic_acl_get(struct inode *inode, struct generic_acl_operations *ops,
		int type, void *buffer, size_t size)
{
	struct posix_acl *acl;
	int error;

	acl = ops->getacl(inode, type);
	if (!acl)
		return -ENODATA;
	error = posix_acl_to_xattr(acl, buffer, size);
	posix_acl_release(acl);

	return error;
}