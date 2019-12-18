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
struct xfs_acl {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ATTR_KERNOVAL ; 
 int ATTR_ROOT ; 
 int /*<<< orphan*/  XFS_I (struct inode*) ; 
 scalar_t__ xfs_attr_get (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int
xfs_acl_exists(struct inode *inode, unsigned char *name)
{
	int len = sizeof(struct xfs_acl);

	return (xfs_attr_get(XFS_I(inode), name, NULL, &len,
			    ATTR_ROOT|ATTR_KERNOVAL) == 0);
}