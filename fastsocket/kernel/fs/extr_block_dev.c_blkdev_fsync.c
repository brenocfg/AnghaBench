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
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct file {TYPE_1__* f_mapping; } ;
struct dentry {int dummy; } ;
struct block_device {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct block_device* I_BDEV (struct inode*) ; 
 int blkdev_issue_flush (struct block_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int blkdev_fsync(struct file *filp, struct dentry *dentry, int datasync)
{
	struct inode *bd_inode = filp->f_mapping->host;
	struct block_device *bdev = I_BDEV(bd_inode);
	int error;

	/*
	 * There is no need to serialise calls to blkdev_issue_flush with
	 * i_mutex and doing so causes performance issues with concurrent
	 * O_SYNC writers to a block device.
	 */
	mutex_unlock(&bd_inode->i_mutex);

	error = blkdev_issue_flush(bdev, NULL);
	if (error == -EOPNOTSUPP)
		error = 0;

	mutex_lock(&bd_inode->i_mutex);

	return error;
}