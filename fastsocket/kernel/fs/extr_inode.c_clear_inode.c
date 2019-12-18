#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nrpages; int /*<<< orphan*/  tree_lock; } ;
struct inode {int i_state; scalar_t__ i_cdev; int /*<<< orphan*/  i_mode; scalar_t__ i_bdev; TYPE_3__* i_sb; TYPE_1__ i_data; } ;
struct TYPE_6__ {TYPE_2__* s_op; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* clear_inode ) (struct inode*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int I_CLEAR ; 
 int I_FREEING ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_forget (struct inode*) ; 
 int /*<<< orphan*/  cd_forget (struct inode*) ; 
 int /*<<< orphan*/  inode_sync_wait (struct inode*) ; 
 int /*<<< orphan*/  invalidate_inode_buffers (struct inode*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_drop (struct inode*) ; 

void clear_inode(struct inode *inode)
{
	might_sleep();
	invalidate_inode_buffers(inode);

	/*
	 * We have to cycle tree_lock here because reclaim can be still in the
	 * process of removing the last page (in __delete_from_page_cache())
	 * and we must not free mapping under it.
	 */
	spin_lock_irq(&inode->i_data.tree_lock);
	BUG_ON(inode->i_data.nrpages);
	spin_unlock_irq(&inode->i_data.tree_lock);
	BUG_ON(!(inode->i_state & I_FREEING));
	BUG_ON(inode->i_state & I_CLEAR);
	inode_sync_wait(inode);
	vfs_dq_drop(inode);
	if (inode->i_sb->s_op->clear_inode)
		inode->i_sb->s_op->clear_inode(inode);
	if (S_ISBLK(inode->i_mode) && inode->i_bdev)
		bd_forget(inode);
	if (S_ISCHR(inode->i_mode) && inode->i_cdev)
		cd_forget(inode);
	inode->i_state = I_CLEAR;
}