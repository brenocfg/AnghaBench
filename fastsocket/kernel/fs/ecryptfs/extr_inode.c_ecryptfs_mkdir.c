#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_sb; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 int ecryptfs_interpose (struct dentry*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsstack_copy_attr_times (struct inode*,TYPE_1__*) ; 
 int /*<<< orphan*/  fsstack_copy_inode_size (struct inode*,TYPE_1__*) ; 
 struct dentry* lock_parent (struct dentry*) ; 
 int /*<<< orphan*/  unlock_dir (struct dentry*) ; 
 int vfs_mkdir (TYPE_1__*,struct dentry*,int) ; 

__attribute__((used)) static int ecryptfs_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	int rc;
	struct dentry *lower_dentry;
	struct dentry *lower_dir_dentry;

	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	lower_dir_dentry = lock_parent(lower_dentry);
	rc = vfs_mkdir(lower_dir_dentry->d_inode, lower_dentry, mode);
	if (rc || !lower_dentry->d_inode)
		goto out;
	rc = ecryptfs_interpose(lower_dentry, dentry, dir->i_sb, 0);
	if (rc)
		goto out;
	fsstack_copy_attr_times(dir, lower_dir_dentry->d_inode);
	fsstack_copy_inode_size(dir, lower_dir_dentry->d_inode);
	dir->i_nlink = lower_dir_dentry->d_inode->i_nlink;
out:
	unlock_dir(lower_dir_dentry);
	if (!dentry->d_inode)
		d_drop(dentry);
	return rc;
}