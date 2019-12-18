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
struct xfs_mount {scalar_t__ m_quotainfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_QMOPT_QUOTALL ; 
 int /*<<< orphan*/  xfs_qm_destroy_quotainfo (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_qm_dqpurge_all (struct xfs_mount*,int /*<<< orphan*/ ) ; 

void
xfs_qm_unmount(
	struct xfs_mount	*mp)
{
	if (mp->m_quotainfo) {
		xfs_qm_dqpurge_all(mp, XFS_QMOPT_QUOTALL);
		xfs_qm_destroy_quotainfo(mp);
	}
}