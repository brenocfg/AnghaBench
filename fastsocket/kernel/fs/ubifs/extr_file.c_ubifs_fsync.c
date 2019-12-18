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
struct ubifs_info {int dummy; } ;
struct inode {int i_state; TYPE_1__* i_sb; int /*<<< orphan*/  i_ino; } ;
struct file {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_4__ {int (* write_inode ) (struct inode*,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {TYPE_2__* s_op; struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int I_DIRTY_DATASYNC ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,int /*<<< orphan*/ *) ; 
 int ubifs_sync_wbufs_by_inode (struct ubifs_info*,struct inode*) ; 

int ubifs_fsync(struct file *file, struct dentry *dentry, int datasync)
{
	struct inode *inode = dentry->d_inode;
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	int err;

	dbg_gen("syncing inode %lu", inode->i_ino);

	/*
	 * VFS has already synchronized dirty pages for this inode. Synchronize
	 * the inode unless this is a 'datasync()' call.
	 */
	if (!datasync || (inode->i_state & I_DIRTY_DATASYNC)) {
		err = inode->i_sb->s_op->write_inode(inode, NULL);
		if (err)
			return err;
	}

	/*
	 * Nodes related to this inode may still sit in a write-buffer. Flush
	 * them.
	 */
	err = ubifs_sync_wbufs_by_inode(c, inode);
	if (err)
		return err;

	return 0;
}