#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int m_qflags; TYPE_1__* m_quotainfo; int /*<<< orphan*/  m_ddev_targp; } ;
typedef  TYPE_2__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_inode_t ;
typedef  scalar_t__ xfs_ino_t ;
typedef  int uint ;
struct TYPE_15__ {int /*<<< orphan*/ * qi_gquotaip; int /*<<< orphan*/ * qi_uquotaip; int /*<<< orphan*/  qi_dqlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int INT_MAX ; 
 scalar_t__ XFS_IS_GQUOTA_ON (TYPE_2__*) ; 
 int XFS_IS_QUOTA_RUNNING (TYPE_2__*) ; 
 int XFS_OQUOTA_CHKD ; 
 int /*<<< orphan*/  XFS_QMOPT_GQUOTA ; 
 int /*<<< orphan*/  XFS_QMOPT_PQUOTA ; 
 int /*<<< orphan*/  XFS_QMOPT_QUOTALL ; 
 int /*<<< orphan*/  XFS_QMOPT_UQUOTA ; 
 int XFS_UQUOTA_CHKD ; 
 int /*<<< orphan*/  XFS_bflush (int /*<<< orphan*/ ) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_Gqm ; 
 int xfs_bulkstat (TYPE_2__*,scalar_t__*,int*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ xfs_mount_reset_sbqflags (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_notice (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  xfs_qm_destroy_quotainfo (TYPE_2__*) ; 
 int xfs_qm_dqflush_all (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqiterate (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_qm_dqpurge_all (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_qm_dquot_list_print (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_qm_dqusage_adjust ; 
 int /*<<< orphan*/  xfs_warn (TYPE_2__*,char*,...) ; 

int
xfs_qm_quotacheck(
	xfs_mount_t	*mp)
{
	int		done, count, error;
	xfs_ino_t	lastino;
	size_t		structsz;
	xfs_inode_t	*uip, *gip;
	uint		flags;

	count = INT_MAX;
	structsz = 1;
	lastino = 0;
	flags = 0;

	ASSERT(mp->m_quotainfo->qi_uquotaip || mp->m_quotainfo->qi_gquotaip);
	ASSERT(XFS_IS_QUOTA_RUNNING(mp));

	/*
	 * There should be no cached dquots. The (simplistic) quotacheck
	 * algorithm doesn't like that.
	 */
	ASSERT(list_empty(&mp->m_quotainfo->qi_dqlist));

	xfs_notice(mp, "Quotacheck needed: Please wait.");

	/*
	 * First we go thru all the dquots on disk, USR and GRP/PRJ, and reset
	 * their counters to zero. We need a clean slate.
	 * We don't log our changes till later.
	 */
	uip = mp->m_quotainfo->qi_uquotaip;
	if (uip) {
		error = xfs_qm_dqiterate(mp, uip, XFS_QMOPT_UQUOTA);
		if (error)
			goto error_return;
		flags |= XFS_UQUOTA_CHKD;
	}

	gip = mp->m_quotainfo->qi_gquotaip;
	if (gip) {
		error = xfs_qm_dqiterate(mp, gip, XFS_IS_GQUOTA_ON(mp) ?
					XFS_QMOPT_GQUOTA : XFS_QMOPT_PQUOTA);
		if (error)
			goto error_return;
		flags |= XFS_OQUOTA_CHKD;
	}

	do {
		/*
		 * Iterate thru all the inodes in the file system,
		 * adjusting the corresponding dquot counters in core.
		 */
		error = xfs_bulkstat(mp, &lastino, &count,
				     xfs_qm_dqusage_adjust,
				     structsz, NULL, &done);
		if (error)
			break;

	} while (!done);

	/*
	 * We've made all the changes that we need to make incore.
	 * Flush them down to disk buffers if everything was updated
	 * successfully.
	 */
	if (!error)
		error = xfs_qm_dqflush_all(mp, 0);

	/*
	 * We can get this error if we couldn't do a dquot allocation inside
	 * xfs_qm_dqusage_adjust (via bulkstat). We don't care about the
	 * dirty dquots that might be cached, we just want to get rid of them
	 * and turn quotaoff. The dquots won't be attached to any of the inodes
	 * at this point (because we intentionally didn't in dqget_noattach).
	 */
	if (error) {
		xfs_qm_dqpurge_all(mp, XFS_QMOPT_QUOTALL);
		goto error_return;
	}

	/*
	 * We didn't log anything, because if we crashed, we'll have to
	 * start the quotacheck from scratch anyway. However, we must make
	 * sure that our dquot changes are secure before we put the
	 * quotacheck'd stamp on the superblock. So, here we do a synchronous
	 * flush.
	 */
	XFS_bflush(mp->m_ddev_targp);

	/*
	 * If one type of quotas is off, then it will lose its
	 * quotachecked status, since we won't be doing accounting for
	 * that type anymore.
	 */
	mp->m_qflags &= ~(XFS_OQUOTA_CHKD | XFS_UQUOTA_CHKD);
	mp->m_qflags |= flags;

	xfs_qm_dquot_list_print(mp);

 error_return:
	if (error) {
		xfs_warn(mp,
	"Quotacheck: Unsuccessful (Error %d): Disabling quotas.",
			error);
		/*
		 * We must turn off quotas.
		 */
		ASSERT(mp->m_quotainfo != NULL);
		ASSERT(xfs_Gqm != NULL);
		xfs_qm_destroy_quotainfo(mp);
		if (xfs_mount_reset_sbqflags(mp)) {
			xfs_warn(mp,
				"Quotacheck: Failed to reset quota flags.");
		}
	} else
		xfs_notice(mp, "Quotacheck: Done.");
	return (error);
}