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
 int ENODATA ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_to_xattr (struct posix_acl*,void*,size_t) ; 
 int xfs_decode_acl (char const*) ; 
 struct posix_acl* xfs_get_acl (struct inode*,int) ; 

__attribute__((used)) static int
xfs_xattr_system_get(struct inode *inode, const char *name,
		void *value, size_t size)
{
	struct posix_acl *acl;
	int type, error;

	type = xfs_decode_acl(name);
	if (type < 0)
		return type;

	acl = xfs_get_acl(inode, type);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	if (acl == NULL)
		return -ENODATA;

	error = posix_acl_to_xattr(acl, value, size);
	posix_acl_release(acl);

	return error;
}