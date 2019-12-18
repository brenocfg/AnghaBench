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
struct super_block {int /*<<< orphan*/  s_bdev; TYPE_1__* s_op; scalar_t__ s_dirt; } ;
struct inode {struct super_block* i_sb; } ;
struct file {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_super ) (struct super_block*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct super_block*) ; 
 int sync_blockdev (int /*<<< orphan*/ ) ; 
 int write_inode_now (struct inode*,int /*<<< orphan*/ ) ; 

int file_fsync(struct file *filp, struct dentry *dentry, int datasync)
{
	struct inode * inode = dentry->d_inode;
	struct super_block * sb;
	int ret, err;

	/* sync the inode to buffers */
	ret = write_inode_now(inode, 0);

	/* sync the superblock to buffers */
	sb = inode->i_sb;
	if (sb->s_dirt && sb->s_op->write_super)
		sb->s_op->write_super(sb);

	/* .. finally sync the buffers to disk */
	err = sync_blockdev(sb->s_bdev);
	if (!ret)
		ret = err;
	return ret;
}