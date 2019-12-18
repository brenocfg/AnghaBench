#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xfs_quotainfo {int /*<<< orphan*/  qi_iwarnlimit; int /*<<< orphan*/  qi_bwarnlimit; int /*<<< orphan*/  qi_rtbtimelimit; int /*<<< orphan*/  qi_itimelimit; int /*<<< orphan*/  qi_btimelimit; int /*<<< orphan*/  qi_dquots; struct xfs_inode* qi_gquotaip; struct xfs_inode* qi_uquotaip; } ;
struct TYPE_8__ {scalar_t__ sb_uquotino; scalar_t__ sb_gquotino; } ;
struct xfs_mount {int m_qflags; TYPE_4__ m_sb; struct xfs_quotainfo* m_quotainfo; } ;
struct TYPE_7__ {int /*<<< orphan*/  di_nextents; int /*<<< orphan*/  di_nblocks; } ;
struct xfs_inode {TYPE_3__ i_d; } ;
struct TYPE_6__ {scalar_t__ qfs_ino; int /*<<< orphan*/  qfs_nextents; int /*<<< orphan*/  qfs_nblks; } ;
struct TYPE_5__ {scalar_t__ qfs_ino; int /*<<< orphan*/  qfs_nextents; int /*<<< orphan*/  qfs_nblks; } ;
struct fs_quota_stat {int /*<<< orphan*/  qs_iwarnlimit; int /*<<< orphan*/  qs_bwarnlimit; int /*<<< orphan*/  qs_rtbtimelimit; int /*<<< orphan*/  qs_itimelimit; int /*<<< orphan*/  qs_btimelimit; int /*<<< orphan*/  qs_incoredqs; TYPE_2__ qs_gquota; TYPE_1__ qs_uquota; scalar_t__ qs_pad; scalar_t__ qs_flags; int /*<<< orphan*/  qs_version; } ;
typedef  int /*<<< orphan*/  fs_quota_stat_t ;
typedef  scalar_t__ boolean_t ;
typedef  scalar_t__ __uint16_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  FS_QSTAT_VERSION ; 
 int /*<<< orphan*/  IRELE (struct xfs_inode*) ; 
 scalar_t__ NULLFSINO ; 
 int XFS_ALL_QUOTA_ACCT ; 
 int XFS_ALL_QUOTA_ENFD ; 
 int /*<<< orphan*/  memset (struct fs_quota_stat*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xfs_iget (struct xfs_mount*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_inode**) ; 
 scalar_t__ xfs_qm_export_flags (int) ; 
 int /*<<< orphan*/  xfs_sb_version_hasquota (TYPE_4__*) ; 

int
xfs_qm_scall_getqstat(
	struct xfs_mount	*mp,
	struct fs_quota_stat	*out)
{
	struct xfs_quotainfo	*q = mp->m_quotainfo;
	struct xfs_inode	*uip, *gip;
	boolean_t		tempuqip, tempgqip;

	uip = gip = NULL;
	tempuqip = tempgqip = B_FALSE;
	memset(out, 0, sizeof(fs_quota_stat_t));

	out->qs_version = FS_QSTAT_VERSION;
	if (!xfs_sb_version_hasquota(&mp->m_sb)) {
		out->qs_uquota.qfs_ino = NULLFSINO;
		out->qs_gquota.qfs_ino = NULLFSINO;
		return (0);
	}
	out->qs_flags = (__uint16_t) xfs_qm_export_flags(mp->m_qflags &
							(XFS_ALL_QUOTA_ACCT|
							 XFS_ALL_QUOTA_ENFD));
	out->qs_pad = 0;
	out->qs_uquota.qfs_ino = mp->m_sb.sb_uquotino;
	out->qs_gquota.qfs_ino = mp->m_sb.sb_gquotino;

	if (q) {
		uip = q->qi_uquotaip;
		gip = q->qi_gquotaip;
	}
	if (!uip && mp->m_sb.sb_uquotino != NULLFSINO) {
		if (xfs_iget(mp, NULL, mp->m_sb.sb_uquotino,
					0, 0, &uip) == 0)
			tempuqip = B_TRUE;
	}
	if (!gip && mp->m_sb.sb_gquotino != NULLFSINO) {
		if (xfs_iget(mp, NULL, mp->m_sb.sb_gquotino,
					0, 0, &gip) == 0)
			tempgqip = B_TRUE;
	}
	if (uip) {
		out->qs_uquota.qfs_nblks = uip->i_d.di_nblocks;
		out->qs_uquota.qfs_nextents = uip->i_d.di_nextents;
		if (tempuqip)
			IRELE(uip);
	}
	if (gip) {
		out->qs_gquota.qfs_nblks = gip->i_d.di_nblocks;
		out->qs_gquota.qfs_nextents = gip->i_d.di_nextents;
		if (tempgqip)
			IRELE(gip);
	}
	if (q) {
		out->qs_incoredqs = q->qi_dquots;
		out->qs_btimelimit = q->qi_btimelimit;
		out->qs_itimelimit = q->qi_itimelimit;
		out->qs_rtbtimelimit = q->qi_rtbtimelimit;
		out->qs_bwarnlimit = q->qi_bwarnlimit;
		out->qs_iwarnlimit = q->qi_iwarnlimit;
	}
	return 0;
}