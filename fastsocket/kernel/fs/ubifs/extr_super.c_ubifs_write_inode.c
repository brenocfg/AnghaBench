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
struct writeback_control {int dummy; } ;
struct ubifs_inode {int /*<<< orphan*/  ui_mutex; scalar_t__ dirty; int /*<<< orphan*/  ui_size; int /*<<< orphan*/  xattr; } ;
struct ubifs_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; scalar_t__ i_nlink; scalar_t__ i_mode; TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int dbg_check_inode_size (struct ubifs_info*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_err (char*,int /*<<< orphan*/ ,int) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_write_inode (struct ubifs_info*,struct inode*) ; 
 int /*<<< orphan*/  ubifs_release_dirty_inode_budget (struct ubifs_info*,struct ubifs_inode*) ; 

__attribute__((used)) static int ubifs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	int err = 0;
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	struct ubifs_inode *ui = ubifs_inode(inode);

	ubifs_assert(!ui->xattr);
	if (is_bad_inode(inode))
		return 0;

	mutex_lock(&ui->ui_mutex);
	/*
	 * Due to races between write-back forced by budgeting
	 * (see 'sync_some_inodes()') and pdflush write-back, the inode may
	 * have already been synchronized, do not do this again. This might
	 * also happen if it was synchronized in an VFS operation, e.g.
	 * 'ubifs_link()'.
	 */
	if (!ui->dirty) {
		mutex_unlock(&ui->ui_mutex);
		return 0;
	}

	/*
	 * As an optimization, do not write orphan inodes to the media just
	 * because this is not needed.
	 */
	dbg_gen("inode %lu, mode %#x, nlink %u",
		inode->i_ino, (int)inode->i_mode, inode->i_nlink);
	if (inode->i_nlink) {
		err = ubifs_jnl_write_inode(c, inode);
		if (err)
			ubifs_err("can't write inode %lu, error %d",
				  inode->i_ino, err);
		else
			err = dbg_check_inode_size(c, inode, ui->ui_size);
	}

	ui->dirty = 0;
	mutex_unlock(&ui->ui_mutex);
	ubifs_release_dirty_inode_budget(c, ui);
	return err;
}