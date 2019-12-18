#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* m_quotainfo; scalar_t__ m_rsumip; scalar_t__ m_rbmip; scalar_t__ m_rootip; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_4__ {int /*<<< orphan*/ * qi_gquotaip; int /*<<< orphan*/ * qi_uquotaip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  IRELE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_qm_dqdetach (scalar_t__) ; 

void
xfs_qm_unmount_quotas(
	xfs_mount_t	*mp)
{
	/*
	 * Release the dquots that root inode, et al might be holding,
	 * before we flush quotas and blow away the quotainfo structure.
	 */
	ASSERT(mp->m_rootip);
	xfs_qm_dqdetach(mp->m_rootip);
	if (mp->m_rbmip)
		xfs_qm_dqdetach(mp->m_rbmip);
	if (mp->m_rsumip)
		xfs_qm_dqdetach(mp->m_rsumip);

	/*
	 * Release the quota inodes.
	 */
	if (mp->m_quotainfo) {
		if (mp->m_quotainfo->qi_uquotaip) {
			IRELE(mp->m_quotainfo->qi_uquotaip);
			mp->m_quotainfo->qi_uquotaip = NULL;
		}
		if (mp->m_quotainfo->qi_gquotaip) {
			IRELE(mp->m_quotainfo->qi_gquotaip);
			mp->m_quotainfo->qi_gquotaip = NULL;
		}
	}
}