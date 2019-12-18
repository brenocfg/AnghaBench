#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_5__ {int /*<<< orphan*/  q_core; } ;
typedef  TYPE_1__ xfs_dquot_t ;
typedef  int /*<<< orphan*/  xfs_dqid_t ;
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  fs_disk_quota_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  ENOENT ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_IS_DQUOT_UNINITIALIZED (TYPE_1__*) ; 
 int xfs_qm_dqget (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  xfs_qm_dqput (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_qm_export_dquot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xfs_qm_scall_getquota(
	xfs_mount_t	*mp,
	xfs_dqid_t	id,
	uint		type,
	fs_disk_quota_t *out)
{
	xfs_dquot_t	*dqp;
	int		error;

	/*
	 * Try to get the dquot. We don't want it allocated on disk, so
	 * we aren't passing the XFS_QMOPT_DOALLOC flag. If it doesn't
	 * exist, we'll get ENOENT back.
	 */
	if ((error = xfs_qm_dqget(mp, NULL, id, type, 0, &dqp))) {
		return (error);
	}

	/*
	 * If everything's NULL, this dquot doesn't quite exist as far as
	 * our utility programs are concerned.
	 */
	if (XFS_IS_DQUOT_UNINITIALIZED(dqp)) {
		xfs_qm_dqput(dqp);
		return XFS_ERROR(ENOENT);
	}
	/* xfs_qm_dqprint(dqp); */
	/*
	 * Convert the disk dquot to the exportable format
	 */
	xfs_qm_export_dquot(mp, &dqp->q_core, out);
	xfs_qm_dqput(dqp);
	return (error ? XFS_ERROR(EFAULT) : 0);
}