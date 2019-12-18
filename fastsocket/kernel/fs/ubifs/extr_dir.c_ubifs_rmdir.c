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
struct ubifs_inode {int ui_size; } ;
struct ubifs_info {scalar_t__ nospace_rp; scalar_t__ nospace; } ;
struct ubifs_budget_req {int mod_dent; int dirtied_ino; } ;
struct inode {int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__ d_name; struct inode* d_inode; } ;
struct TYPE_3__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int CALC_DENT_SIZE (int /*<<< orphan*/ ) ; 
 int ENOSPC ; 
 int check_dir_empty (struct ubifs_info*,struct inode*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  lock_2_inodes (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_current_time (struct inode*) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_update (struct ubifs_info*,struct inode*,TYPE_2__*,struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  unlock_2_inodes (struct inode*,struct inode*) ; 

__attribute__((used)) static int ubifs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct ubifs_info *c = dir->i_sb->s_fs_info;
	struct inode *inode = dentry->d_inode;
	int sz_change = CALC_DENT_SIZE(dentry->d_name.len);
	int err, budgeted = 1;
	struct ubifs_inode *dir_ui = ubifs_inode(dir);
	struct ubifs_budget_req req = { .mod_dent = 1, .dirtied_ino = 2 };

	/*
	 * Budget request settings: deletion direntry, deletion inode and
	 * changing the parent inode. If budgeting fails, go ahead anyway
	 * because we have extra space reserved for deletions.
	 */

	dbg_gen("directory '%.*s', ino %lu in dir ino %lu", dentry->d_name.len,
		dentry->d_name.name, inode->i_ino, dir->i_ino);
	ubifs_assert(mutex_is_locked(&dir->i_mutex));
	ubifs_assert(mutex_is_locked(&inode->i_mutex));
	err = check_dir_empty(c, dentry->d_inode);
	if (err)
		return err;

	err = ubifs_budget_space(c, &req);
	if (err) {
		if (err != -ENOSPC)
			return err;
		budgeted = 0;
	}

	lock_2_inodes(dir, inode);
	inode->i_ctime = ubifs_current_time(dir);
	clear_nlink(inode);
	drop_nlink(dir);
	dir->i_size -= sz_change;
	dir_ui->ui_size = dir->i_size;
	dir->i_mtime = dir->i_ctime = inode->i_ctime;
	err = ubifs_jnl_update(c, dir, &dentry->d_name, inode, 1, 0);
	if (err)
		goto out_cancel;
	unlock_2_inodes(dir, inode);

	if (budgeted)
		ubifs_release_budget(c, &req);
	else {
		/* We've deleted something - clean the "no space" flags */
		c->nospace = c->nospace_rp = 0;
		smp_wmb();
	}
	return 0;

out_cancel:
	dir->i_size += sz_change;
	dir_ui->ui_size = dir->i_size;
	inc_nlink(dir);
	inc_nlink(inode);
	inc_nlink(inode);
	unlock_2_inodes(dir, inode);
	if (budgeted)
		ubifs_release_budget(c, &req);
	return err;
}