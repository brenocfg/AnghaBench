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
struct writeback_control {scalar_t__ sync_mode; } ;
struct super_block {int dummy; } ;
struct object_info {int /*<<< orphan*/  size; int /*<<< orphan*/  attr; int /*<<< orphan*/  execaddr; int /*<<< orphan*/  loadaddr; int /*<<< orphan*/  parent_id; scalar_t__ name_len; int /*<<< orphan*/  file_id; } ;
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  attr; int /*<<< orphan*/  execaddr; int /*<<< orphan*/  loadaddr; int /*<<< orphan*/  parent_id; } ;

/* Variables and functions */
 TYPE_1__* ADFS_I (struct inode*) ; 
 scalar_t__ WB_SYNC_ALL ; 
 int adfs_dir_update (struct super_block*,struct object_info*,int) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

int adfs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	struct super_block *sb = inode->i_sb;
	struct object_info obj;
	int ret;

	lock_kernel();
	obj.file_id	= inode->i_ino;
	obj.name_len	= 0;
	obj.parent_id	= ADFS_I(inode)->parent_id;
	obj.loadaddr	= ADFS_I(inode)->loadaddr;
	obj.execaddr	= ADFS_I(inode)->execaddr;
	obj.attr	= ADFS_I(inode)->attr;
	obj.size	= inode->i_size;

	ret = adfs_dir_update(sb, &obj, wbc->sync_mode == WB_SYNC_ALL);
	unlock_kernel();
	return ret;
}