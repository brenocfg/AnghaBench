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
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_inode; int /*<<< orphan*/  d_count; TYPE_2__ d_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_rehash (struct dentry*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dcache_lock ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_safe_remove (struct dentry*) ; 
 int /*<<< orphan*/  nfs_save_change_attribute (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_verifier (struct dentry*,int /*<<< orphan*/ ) ; 
 int nfs_sillyrename (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_inode_now (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_unlink(struct inode *dir, struct dentry *dentry)
{
	int error;
	int need_rehash = 0;

	dfprintk(VFS, "NFS: unlink(%s/%ld, %s)\n", dir->i_sb->s_id,
		dir->i_ino, dentry->d_name.name);

	spin_lock(&dcache_lock);
	spin_lock(&dentry->d_lock);
	if (atomic_read(&dentry->d_count) > 1) {
		spin_unlock(&dentry->d_lock);
		spin_unlock(&dcache_lock);
		/* Start asynchronous writeout of the inode */
		write_inode_now(dentry->d_inode, 0);
		error = nfs_sillyrename(dir, dentry);
		return error;
	}
	if (!d_unhashed(dentry)) {
		__d_drop(dentry);
		need_rehash = 1;
	}
	spin_unlock(&dentry->d_lock);
	spin_unlock(&dcache_lock);
	error = nfs_safe_remove(dentry);
	if (!error || error == -ENOENT) {
		nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
	} else if (need_rehash)
		d_rehash(dentry);
	return error;
}