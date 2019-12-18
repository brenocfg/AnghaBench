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
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int OCFS2_MOUNT_POSIX_ACL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 
 int ocfs2_set_acl (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,int,struct posix_acl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct posix_acl* posix_acl_from_xattr (void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_valid (struct posix_acl*) ; 

__attribute__((used)) static int ocfs2_xattr_set_acl(struct inode *inode,
			       int type,
			       const void *value,
			       size_t size)
{
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct posix_acl *acl;
	int ret = 0;

	if (!(osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL))
		return -EOPNOTSUPP;

	if (!is_owner_or_cap(inode))
		return -EPERM;

	if (value) {
		acl = posix_acl_from_xattr(value, size);
		if (IS_ERR(acl))
			return PTR_ERR(acl);
		else if (acl) {
			ret = posix_acl_valid(acl);
			if (ret)
				goto cleanup;
		}
	} else
		acl = NULL;

	ret = ocfs2_set_acl(NULL, inode, NULL, type, acl, NULL, NULL);

cleanup:
	posix_acl_release(acl);
	return ret;
}