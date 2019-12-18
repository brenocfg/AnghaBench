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
typedef  int ssize_t ;

/* Variables and functions */
 int __jfs_getxattr (int /*<<< orphan*/ ,char const*,void*,size_t) ; 

ssize_t jfs_getxattr(struct dentry *dentry, const char *name, void *data,
		     size_t buf_size)
{
	int err;

	err = __jfs_getxattr(dentry->d_inode, name, data, buf_size);

	return err;
}