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
struct ocfs2_super {int s_mount_opt; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int OCFS2_MOUNT_NOUSERXATTR ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCFS2_XATTR_INDEX_USER ; 
 int ocfs2_xattr_set (struct inode*,int /*<<< orphan*/ ,char const*,void const*,size_t,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int ocfs2_xattr_user_set(struct inode *inode, const char *name,
				const void *value, size_t size, int flags)
{
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	if (strcmp(name, "") == 0)
		return -EINVAL;
	if (osb->s_mount_opt & OCFS2_MOUNT_NOUSERXATTR)
		return -EOPNOTSUPP;

	return ocfs2_xattr_set(inode, OCFS2_XATTR_INDEX_USER, name, value,
			       size, flags);
}