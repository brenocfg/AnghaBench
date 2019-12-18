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
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  XATTR_USER_PREFIX ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int reiserfs_xattr_set (struct inode*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  reiserfs_xattrs_user (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
user_set(struct inode *inode, const char *name, const void *buffer,
	 size_t size, int flags)
{
	if (strlen(name) < sizeof(XATTR_USER_PREFIX))
		return -EINVAL;

	if (!reiserfs_xattrs_user(inode->i_sb))
		return -EOPNOTSUPP;
	return reiserfs_xattr_set(inode, name, buffer, size, flags);
}