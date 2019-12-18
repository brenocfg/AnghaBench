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
struct writeback_control {int /*<<< orphan*/  nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct inode {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int sync_inode (struct inode*,struct writeback_control*) ; 

__attribute__((used)) static int pohmelfs_fsync(struct file *file, struct dentry *dentry, int datasync)
{
	struct inode *inode = file->f_mapping->host;
	struct writeback_control wbc = {
		.sync_mode = WB_SYNC_ALL,
		.nr_to_write = 0,	/* sys_fsync did this */
	};

	return sync_inode(inode, &wbc);
}