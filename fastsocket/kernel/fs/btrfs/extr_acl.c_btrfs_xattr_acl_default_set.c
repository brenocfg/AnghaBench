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
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int btrfs_xattr_set_acl (struct inode*,int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int btrfs_xattr_acl_default_set(struct inode *inode, const char *name,
			       const void *value, size_t size, int flags)
{
	return btrfs_xattr_set_acl(inode, ACL_TYPE_DEFAULT, value, size);
}