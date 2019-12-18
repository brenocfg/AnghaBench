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
 int btrfs_xattr_get_acl (struct inode*,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int btrfs_xattr_acl_access_get(struct inode *inode, const char *name,
				      void *value, size_t size)
{
	return btrfs_xattr_get_acl(inode, ACL_TYPE_ACCESS, value, size);
}