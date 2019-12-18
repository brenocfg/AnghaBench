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
 struct posix_acl* jffs2_get_acl (struct inode*,int) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_to_xattr (struct posix_acl*,void*,size_t) ; 

__attribute__((used)) static int jffs2_acl_getxattr(struct inode *inode, int type, void *buffer, size_t size)
{
	struct posix_acl *acl;
	int rc;

	acl = jffs2_get_acl(inode, type);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	if (!acl)
		return -ENODATA;
	rc = posix_acl_to_xattr(acl, buffer, size);
	posix_acl_release(acl);

	return rc;
}