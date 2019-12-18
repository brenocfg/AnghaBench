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
struct TYPE_2__ {int /*<<< orphan*/ * w_completion; struct xfs_mount* w_mount; int /*<<< orphan*/  w_syncer; } ;
struct xfs_mount {int /*<<< orphan*/  m_sync_task; int /*<<< orphan*/  m_fsname; TYPE_1__ m_sync_work; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct xfs_mount*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sync_worker ; 
 int /*<<< orphan*/  xfssyncd ; 

int
xfs_syncd_init(
	struct xfs_mount	*mp)
{
	mp->m_sync_work.w_syncer = xfs_sync_worker;
	mp->m_sync_work.w_mount = mp;
	mp->m_sync_work.w_completion = NULL;
	mp->m_sync_task = kthread_run(xfssyncd, mp, "xfssyncd/%s", mp->m_fsname);
	if (IS_ERR(mp->m_sync_task))
		return -PTR_ERR(mp->m_sync_task);
	return 0;
}