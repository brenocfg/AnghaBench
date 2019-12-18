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
struct ubifs_inode {int ui_size; int /*<<< orphan*/  data_len; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int new_dent; int dirtied_ino; int /*<<< orphan*/  dirtied_ino_d; } ;
struct inode {scalar_t__ i_nlink; int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_count; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__ d_name; struct inode* d_inode; } ;
struct TYPE_3__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int CALC_DENT_SIZE (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int dbg_check_synced_i_size (struct inode*) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  lock_2_inodes (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_current_time (struct inode*) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_update (struct ubifs_info*,struct inode*,TYPE_2__*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  unlock_2_inodes (struct inode*,struct inode*) ; 

__attribute__((used)) static int ubifs_link(struct dentry *old_dentry, struct inode *dir,
		      struct dentry *dentry)
{
	struct ubifs_info *c = dir->i_sb->s_fs_info;
	struct inode *inode = old_dentry->d_inode;
	struct ubifs_inode *ui = ubifs_inode(inode);
	struct ubifs_inode *dir_ui = ubifs_inode(dir);
	int err, sz_change = CALC_DENT_SIZE(dentry->d_name.len);
	struct ubifs_budget_req req = { .new_dent = 1, .dirtied_ino = 2,
				.dirtied_ino_d = ALIGN(ui->data_len, 8) };

	/*
	 * Budget request settings: new direntry, changing the target inode,
	 * changing the parent inode.
	 */

	dbg_gen("dent '%.*s' to ino %lu (nlink %d) in dir ino %lu",
		dentry->d_name.len, dentry->d_name.name, inode->i_ino,
		inode->i_nlink, dir->i_ino);
	ubifs_assert(mutex_is_locked(&dir->i_mutex));
	ubifs_assert(mutex_is_locked(&inode->i_mutex));

	/*
	 * Return -ENOENT if we've raced with unlink and i_nlink is 0.  Doing
	 * otherwise has the potential to corrupt the orphan inode list.
	 *
	 * Indeed, consider a scenario when 'vfs_link(dirA/fileA)' and
	 * 'vfs_unlink(dirA/fileA, dirB/fileB)' race. 'vfs_link()' does not
	 * lock 'dirA->i_mutex', so this is possible. Both of the functions
	 * lock 'fileA->i_mutex' though. Suppose 'vfs_unlink()' wins, and takes
	 * 'fileA->i_mutex' mutex first. Suppose 'fileA->i_nlink' is 1. In this
	 * case 'ubifs_unlink()' will drop the last reference, and put 'inodeA'
	 * to the list of orphans. After this, 'vfs_link()' will link
	 * 'dirB/fileB' to 'inodeA'. This is a problem because, for example,
	 * the subsequent 'vfs_unlink(dirB/fileB)' will add the same inode
	 * to the list of orphans.
	 */
	 if (inode->i_nlink == 0)
		 return -ENOENT;

	err = dbg_check_synced_i_size(inode);
	if (err)
		return err;

	err = ubifs_budget_space(c, &req);
	if (err)
		return err;

	lock_2_inodes(dir, inode);
	inc_nlink(inode);
	atomic_inc(&inode->i_count);
	inode->i_ctime = ubifs_current_time(inode);
	dir->i_size += sz_change;
	dir_ui->ui_size = dir->i_size;
	dir->i_mtime = dir->i_ctime = inode->i_ctime;
	err = ubifs_jnl_update(c, dir, &dentry->d_name, inode, 0, 0);
	if (err)
		goto out_cancel;
	unlock_2_inodes(dir, inode);

	ubifs_release_budget(c, &req);
	d_instantiate(dentry, inode);
	return 0;

out_cancel:
	dir->i_size -= sz_change;
	dir_ui->ui_size = dir->i_size;
	drop_nlink(inode);
	unlock_2_inodes(dir, inode);
	ubifs_release_budget(c, &req);
	iput(inode);
	return err;
}