#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/  d_name; TYPE_2__* d_inode; } ;
typedef  int /*<<< orphan*/  btree_key ;
struct TYPE_4__ {int /*<<< orphan*/  i_ino; } ;
struct TYPE_3__ {int /*<<< orphan*/  cat_key; } ;

/* Variables and functions */
 TYPE_1__* HFS_I (TYPE_2__*) ; 
 int /*<<< orphan*/  hfs_cat_build_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hfs_cat_move (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *) ; 
 int hfs_unlink (struct inode*,struct dentry*) ; 

__attribute__((used)) static int hfs_rename(struct inode *old_dir, struct dentry *old_dentry,
		      struct inode *new_dir, struct dentry *new_dentry)
{
	int res;

	/* Unlink destination if it already exists */
	if (new_dentry->d_inode) {
		res = hfs_unlink(new_dir, new_dentry);
		if (res)
			return res;
	}

	res = hfs_cat_move(old_dentry->d_inode->i_ino,
			   old_dir, &old_dentry->d_name,
			   new_dir, &new_dentry->d_name);
	if (!res)
		hfs_cat_build_key(old_dir->i_sb,
				  (btree_key *)&HFS_I(old_dentry->d_inode)->cat_key,
				  new_dir->i_ino, &new_dentry->d_name);
	return res;
}