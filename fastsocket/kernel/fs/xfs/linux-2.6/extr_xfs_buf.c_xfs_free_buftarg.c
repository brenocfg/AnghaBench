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
struct xfs_mount {int m_flags; } ;
struct xfs_buftarg {int /*<<< orphan*/  bt_task; int /*<<< orphan*/  bt_shrinker; } ;

/* Variables and functions */
 int XFS_MOUNT_BARRIER ; 
 int /*<<< orphan*/  kmem_free (struct xfs_buftarg*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_shrinker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_blkdev_issue_flush (struct xfs_buftarg*) ; 
 int /*<<< orphan*/  xfs_flush_buftarg (struct xfs_buftarg*,int) ; 

void
xfs_free_buftarg(
	struct xfs_mount	*mp,
	struct xfs_buftarg	*btp)
{
	unregister_shrinker(&btp->bt_shrinker);

	xfs_flush_buftarg(btp, 1);
	if (mp->m_flags & XFS_MOUNT_BARRIER)
		xfs_blkdev_issue_flush(btp);

	kthread_stop(btp->bt_task);
	kmem_free(btp);
}