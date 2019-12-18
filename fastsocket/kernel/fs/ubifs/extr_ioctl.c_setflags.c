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
struct ubifs_inode {int dirty; int /*<<< orphan*/  ui_mutex; int /*<<< orphan*/  flags; int /*<<< orphan*/  data_len; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int dirtied_ino; int /*<<< orphan*/  dirtied_ino_d; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_ctime; TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_LINUX_IMMUTABLE ; 
 int EPERM ; 
 int FS_APPEND_FL ; 
 int FS_IMMUTABLE_FL ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl2ubifs (int) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ubifs2ioctl (int /*<<< orphan*/ ) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_current_time (struct inode*) ; 
 int /*<<< orphan*/  ubifs_err (char*,int /*<<< orphan*/ ) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_set_inode_flags (struct inode*) ; 
 int write_inode_now (struct inode*,int) ; 

__attribute__((used)) static int setflags(struct inode *inode, int flags)
{
	int oldflags, err, release;
	struct ubifs_inode *ui = ubifs_inode(inode);
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	struct ubifs_budget_req req = { .dirtied_ino = 1,
					.dirtied_ino_d = ui->data_len };

	err = ubifs_budget_space(c, &req);
	if (err)
		return err;

	/*
	 * The IMMUTABLE and APPEND_ONLY flags can only be changed by
	 * the relevant capability.
	 */
	mutex_lock(&ui->ui_mutex);
	oldflags = ubifs2ioctl(ui->flags);
	if ((flags ^ oldflags) & (FS_APPEND_FL | FS_IMMUTABLE_FL)) {
		if (!capable(CAP_LINUX_IMMUTABLE)) {
			err = -EPERM;
			goto out_unlock;
		}
	}

	ui->flags = ioctl2ubifs(flags);
	ubifs_set_inode_flags(inode);
	inode->i_ctime = ubifs_current_time(inode);
	release = ui->dirty;
	mark_inode_dirty_sync(inode);
	mutex_unlock(&ui->ui_mutex);

	if (release)
		ubifs_release_budget(c, &req);
	if (IS_SYNC(inode))
		err = write_inode_now(inode, 1);
	return err;

out_unlock:
	ubifs_err("can't modify inode %lu attributes", inode->i_ino);
	mutex_unlock(&ui->ui_mutex);
	ubifs_release_budget(c, &req);
	return err;
}