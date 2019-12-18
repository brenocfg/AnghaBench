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
struct writeback_control {scalar_t__ sync_mode; scalar_t__ for_background; scalar_t__ nonblocking; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_LAYOUTCOMMIT ; 
 scalar_t__ WB_SYNC_NONE ; 
 int nfs_commit_unstable_pages (struct inode*,struct writeback_control*) ; 
 int pnfs_layoutcommit_inode (struct inode*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nfs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	int ret;

	ret = nfs_commit_unstable_pages(inode, wbc);
	if (ret >= 0 && test_bit(NFS_INO_LAYOUTCOMMIT, &NFS_I(inode)->flags)) {
		int status;
		bool sync = true;

		if (wbc->sync_mode == WB_SYNC_NONE || wbc->nonblocking ||
		    wbc->for_background)
			sync = false;

		status = pnfs_layoutcommit_inode(inode, sync);
		if (status < 0)
			return status;
	}
	return ret;
}