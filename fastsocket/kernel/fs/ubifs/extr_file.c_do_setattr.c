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
struct ubifs_inode {int dirty; int /*<<< orphan*/  ui_mutex; int /*<<< orphan*/  ui_size; int /*<<< orphan*/  data_len; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int dirtied_ino; int /*<<< orphan*/  dirtied_ino_d; } ;
struct inode {TYPE_2__* i_sb; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_size; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {TYPE_1__* s_op; } ;
struct TYPE_3__ {int (* write_inode ) (struct inode*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int ATTR_SIZE ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int I_DIRTY_DATASYNC ; 
 int I_DIRTY_SYNC ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_attr_changes (struct inode*,struct iattr const*) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct inode*,int /*<<< orphan*/ *) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_current_time (struct inode*) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int vmtruncate (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_setattr(struct ubifs_info *c, struct inode *inode,
		      const struct iattr *attr)
{
	int err, release;
	loff_t new_size = attr->ia_size;
	struct ubifs_inode *ui = ubifs_inode(inode);
	struct ubifs_budget_req req = { .dirtied_ino = 1,
				.dirtied_ino_d = ALIGN(ui->data_len, 8) };

	err = ubifs_budget_space(c, &req);
	if (err)
		return err;

	if (attr->ia_valid & ATTR_SIZE) {
		dbg_gen("size %lld -> %lld", inode->i_size, new_size);
		err = vmtruncate(inode, new_size);
		if (err)
			goto out;
	}

	mutex_lock(&ui->ui_mutex);
	if (attr->ia_valid & ATTR_SIZE) {
		/* Truncation changes inode [mc]time */
		inode->i_mtime = inode->i_ctime = ubifs_current_time(inode);
		/* 'vmtruncate()' changed @i_size, update @ui_size */
		ui->ui_size = inode->i_size;
	}

	do_attr_changes(inode, attr);

	release = ui->dirty;
	if (attr->ia_valid & ATTR_SIZE)
		/*
		 * Inode length changed, so we have to make sure
		 * @I_DIRTY_DATASYNC is set.
		 */
		 __mark_inode_dirty(inode, I_DIRTY_SYNC | I_DIRTY_DATASYNC);
	else
		mark_inode_dirty_sync(inode);
	mutex_unlock(&ui->ui_mutex);

	if (release)
		ubifs_release_budget(c, &req);
	if (IS_SYNC(inode))
		err = inode->i_sb->s_op->write_inode(inode, NULL);
	return err;

out:
	ubifs_release_budget(c, &req);
	return err;
}