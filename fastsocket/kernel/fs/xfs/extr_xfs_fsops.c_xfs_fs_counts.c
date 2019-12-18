#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sb_icount; int /*<<< orphan*/  sb_ifree; int /*<<< orphan*/  sb_frextents; scalar_t__ sb_fdblocks; } ;
struct TYPE_9__ {int /*<<< orphan*/  m_sb_lock; TYPE_1__ m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_10__ {int /*<<< orphan*/  allocino; int /*<<< orphan*/  freeino; int /*<<< orphan*/  freertx; scalar_t__ freedata; } ;
typedef  TYPE_3__ xfs_fsop_counts_t ;

/* Variables and functions */
 scalar_t__ XFS_ALLOC_SET_ASIDE (TYPE_2__*) ; 
 int /*<<< orphan*/  XFS_ICSB_LAZY_COUNT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_icsb_sync_counters (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
xfs_fs_counts(
	xfs_mount_t		*mp,
	xfs_fsop_counts_t	*cnt)
{
	xfs_icsb_sync_counters(mp, XFS_ICSB_LAZY_COUNT);
	spin_lock(&mp->m_sb_lock);
	cnt->freedata = mp->m_sb.sb_fdblocks - XFS_ALLOC_SET_ASIDE(mp);
	cnt->freertx = mp->m_sb.sb_frextents;
	cnt->freeino = mp->m_sb.sb_ifree;
	cnt->allocino = mp->m_sb.sb_icount;
	spin_unlock(&mp->m_sb_lock);
	return 0;
}