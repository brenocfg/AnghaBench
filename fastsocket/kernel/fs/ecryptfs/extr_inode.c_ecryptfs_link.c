#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_9__ {int /*<<< orphan*/  i_nlink; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 TYPE_6__* ecryptfs_inode_to_lower (TYPE_1__*) ; 
 int ecryptfs_interpose (struct dentry*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsstack_copy_attr_times (struct inode*,TYPE_1__*) ; 
 int /*<<< orphan*/  fsstack_copy_inode_size (struct inode*,TYPE_1__*) ; 
 int /*<<< orphan*/  i_size_read (TYPE_1__*) ; 
 int /*<<< orphan*/  i_size_write (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct dentry* lock_parent (struct dentry*) ; 
 int /*<<< orphan*/  unlock_dir (struct dentry*) ; 
 int vfs_link (struct dentry*,TYPE_1__*,struct dentry*) ; 

__attribute__((used)) static int ecryptfs_link(struct dentry *old_dentry, struct inode *dir,
			 struct dentry *new_dentry)
{
	struct dentry *lower_old_dentry;
	struct dentry *lower_new_dentry;
	struct dentry *lower_dir_dentry;
	u64 file_size_save;
	int rc;

	file_size_save = i_size_read(old_dentry->d_inode);
	lower_old_dentry = ecryptfs_dentry_to_lower(old_dentry);
	lower_new_dentry = ecryptfs_dentry_to_lower(new_dentry);
	dget(lower_old_dentry);
	dget(lower_new_dentry);
	lower_dir_dentry = lock_parent(lower_new_dentry);
	rc = vfs_link(lower_old_dentry, lower_dir_dentry->d_inode,
		      lower_new_dentry);
	if (rc || !lower_new_dentry->d_inode)
		goto out_lock;
	rc = ecryptfs_interpose(lower_new_dentry, new_dentry, dir->i_sb, 0);
	if (rc)
		goto out_lock;
	fsstack_copy_attr_times(dir, lower_new_dentry->d_inode);
	fsstack_copy_inode_size(dir, lower_new_dentry->d_inode);
	old_dentry->d_inode->i_nlink =
		ecryptfs_inode_to_lower(old_dentry->d_inode)->i_nlink;
	i_size_write(new_dentry->d_inode, file_size_save);
out_lock:
	unlock_dir(lower_dir_dentry);
	dput(lower_new_dentry);
	dput(lower_old_dentry);
	d_drop(lower_old_dentry);
	d_drop(new_dentry);
	d_drop(old_dentry);
	return rc;
}