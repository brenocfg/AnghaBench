#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_1__* d_inode; struct dentry* d_parent; } ;
struct autofs_sb_info {int dummy; } ;
struct autofs_info {int /*<<< orphan*/  dentry; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {scalar_t__ i_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EACCES ; 
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs4_add_expiring (struct dentry*) ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  autofs4_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (TYPE_1__*) ; 
 int /*<<< orphan*/  dcache_lock ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int autofs4_dir_unlink(struct inode *dir, struct dentry *dentry)
{
	struct autofs_sb_info *sbi = autofs4_sbi(dir->i_sb);
	struct autofs_info *ino = autofs4_dentry_ino(dentry);
	struct autofs_info *p_ino;
	
	/* This allows root to remove symlinks */
	if (!autofs4_oz_mode(sbi) && !capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (atomic_dec_and_test(&ino->count)) {
		p_ino = autofs4_dentry_ino(dentry->d_parent);
		if (p_ino && dentry->d_parent != dentry)
			atomic_dec(&p_ino->count);
	}
	dput(ino->dentry);

	dentry->d_inode->i_size = 0;
	clear_nlink(dentry->d_inode);

	dir->i_mtime = CURRENT_TIME;

	spin_lock(&dcache_lock);
	autofs4_add_expiring(dentry);
	spin_lock(&dentry->d_lock);
	__d_drop(dentry);
	spin_unlock(&dentry->d_lock);
	spin_unlock(&dcache_lock);

	return 0;
}