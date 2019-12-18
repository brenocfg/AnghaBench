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
struct ocfs2_super {int s_mount_opt; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int ENODATA ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int OCFS2_MOUNT_POSIX_ACL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct posix_acl*) ; 
 struct posix_acl* ocfs2_get_acl (struct inode*,int) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_to_xattr (struct posix_acl*,void*,size_t) ; 

__attribute__((used)) static int ocfs2_xattr_get_acl(struct inode *inode,
			       int type,
			       void *buffer,
			       size_t size)
{
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct posix_acl *acl;
	int ret;

	if (!(osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL))
		return -EOPNOTSUPP;

	acl = ocfs2_get_acl(inode, type);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	if (acl == NULL)
		return -ENODATA;
	ret = posix_acl_to_xattr(acl, buffer, size);
	posix_acl_release(acl);

	return ret;
}