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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;

/* Variables and functions */
 int btrfs_log_inode_parent (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

int btrfs_log_dentry_safe(struct btrfs_trans_handle *trans,
			  struct btrfs_root *root, struct dentry *dentry)
{
	struct dentry *parent = dget_parent(dentry);
	int ret;

	ret = btrfs_log_inode_parent(trans, root, dentry->d_inode, parent, 0);
	dput(parent);

	return ret;
}