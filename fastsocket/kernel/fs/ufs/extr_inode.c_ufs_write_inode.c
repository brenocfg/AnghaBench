#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct writeback_control {scalar_t__ sync_mode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int ufs_update_inode (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

int ufs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	int ret;
	lock_kernel();
	ret = ufs_update_inode(inode, wbc->sync_mode == WB_SYNC_ALL);
	unlock_kernel();
	return ret;
}