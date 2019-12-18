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
struct dentry {int /*<<< orphan*/  d_inode; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_xattr_list (int /*<<< orphan*/ ,char*,size_t) ; 

ssize_t
ext4_listxattr(struct dentry *dentry, char *buffer, size_t size)
{
	return ext4_xattr_list(dentry->d_inode, buffer, size);
}