#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 struct inode* VFS_I (TYPE_1__*) ; 
 int /*<<< orphan*/  XFS_LOG_SYNC ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_flush_inodes_work ; 
 int /*<<< orphan*/  xfs_log_force (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_syncd_queue_work (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
xfs_flush_inodes(
	xfs_inode_t	*ip)
{
	struct inode	*inode = VFS_I(ip);
	DECLARE_COMPLETION_ONSTACK(completion);

	igrab(inode);
	xfs_syncd_queue_work(ip->i_mount, inode, xfs_flush_inodes_work, &completion);
	wait_for_completion(&completion);
	xfs_log_force(ip->i_mount, XFS_LOG_SYNC);
}