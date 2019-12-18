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
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__* d_inode; struct dentry* d_parent; int /*<<< orphan*/  d_lock; TYPE_1__ d_name; } ;
struct autofs_sb_info {int version; } ;
struct autofs_info {int /*<<< orphan*/  dentry; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {scalar_t__ i_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 int /*<<< orphan*/  __simple_empty (struct dentry*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs4_add_expiring (struct dentry*) ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  autofs4_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autofs_clear_leaf_automount_flags (struct dentry*) ; 
 int /*<<< orphan*/  clear_nlink (TYPE_2__*) ; 
 int /*<<< orphan*/  dcache_lock ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int autofs4_dir_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct autofs_sb_info *sbi = autofs4_sbi(dir->i_sb);
	struct autofs_info *ino = autofs4_dentry_ino(dentry);
	struct autofs_info *p_ino;
	
	DPRINTK("dentry %p, removing %.*s",
		dentry, dentry->d_name.len, dentry->d_name.name);

	if (!autofs4_oz_mode(sbi))
		return -EACCES;

	spin_lock(&dcache_lock);
	if (!__simple_empty(dentry)) {
		spin_unlock(&dcache_lock);
		return -ENOTEMPTY;
	}
	autofs4_add_expiring(dentry);
	spin_lock(&dentry->d_lock);
	__d_drop(dentry);
	spin_unlock(&dentry->d_lock);
	spin_unlock(&dcache_lock);

	if (sbi->version < 5)
		autofs_clear_leaf_automount_flags(dentry);

	if (atomic_dec_and_test(&ino->count)) {
		p_ino = autofs4_dentry_ino(dentry->d_parent);
		if (p_ino && dentry->d_parent != dentry)
			atomic_dec(&p_ino->count);
	}
	dput(ino->dentry);
	dentry->d_inode->i_size = 0;
	clear_nlink(dentry->d_inode);

	if (dir->i_nlink)
		drop_nlink(dir);

	return 0;
}