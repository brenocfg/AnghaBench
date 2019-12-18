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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGI_ACL_DEFAULT ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int xfs_acl_exists (struct inode*,int /*<<< orphan*/ ) ; 

int
posix_acl_default_exists(struct inode *inode)
{
	if (!S_ISDIR(inode->i_mode))
		return 0;
	return xfs_acl_exists(inode, SGI_ACL_DEFAULT);
}