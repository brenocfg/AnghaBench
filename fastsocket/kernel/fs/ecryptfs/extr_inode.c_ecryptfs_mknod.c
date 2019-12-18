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
struct dentry {int /*<<< orphan*/  d_inode; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 int ecryptfs_interpose (struct dentry*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsstack_copy_attr_times (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsstack_copy_inode_size (struct inode*,int /*<<< orphan*/ ) ; 
 struct dentry* lock_parent (struct dentry*) ; 
 int /*<<< orphan*/  unlock_dir (struct dentry*) ; 
 int vfs_mknod (int /*<<< orphan*/ ,struct dentry*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ecryptfs_mknod(struct inode *dir, struct dentry *dentry, int mode, dev_t dev)
{
	int rc;
	struct dentry *lower_dentry;
	struct dentry *lower_dir_dentry;

	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	lower_dir_dentry = lock_parent(lower_dentry);
	rc = vfs_mknod(lower_dir_dentry->d_inode, lower_dentry, mode, dev);
	if (rc || !lower_dentry->d_inode)
		goto out;
	rc = ecryptfs_interpose(lower_dentry, dentry, dir->i_sb, 0);
	if (rc)
		goto out;
	fsstack_copy_attr_times(dir, lower_dir_dentry->d_inode);
	fsstack_copy_inode_size(dir, lower_dir_dentry->d_inode);
out:
	unlock_dir(lower_dir_dentry);
	if (!dentry->d_inode)
		d_drop(dentry);
	return rc;
}