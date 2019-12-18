#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * t_dqinfo; TYPE_3__* t_mountp; } ;
typedef  TYPE_2__ xfs_trans_t ;
struct TYPE_13__ {scalar_t__ sb_uquotino; scalar_t__ sb_gquotino; } ;
struct TYPE_15__ {TYPE_1__ m_sb; } ;
typedef  TYPE_3__ xfs_mount_t ;
struct TYPE_16__ {scalar_t__ i_ino; scalar_t__ i_gdquot; scalar_t__ i_udquot; } ;
typedef  TYPE_4__ xfs_inode_t ;
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 scalar_t__ XFS_IS_OQUOTA_ON (TYPE_3__*) ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_ON (TYPE_3__*) ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_RUNNING (TYPE_3__*) ; 
 scalar_t__ XFS_IS_UQUOTA_ON (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_trans_alloc_dqinfo (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_trans_mod_dquot (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,long) ; 

void
xfs_trans_mod_dquot_byino(
	xfs_trans_t	*tp,
	xfs_inode_t	*ip,
	uint		field,
	long		delta)
{
	xfs_mount_t	*mp = tp->t_mountp;

	if (!XFS_IS_QUOTA_RUNNING(mp) ||
	    !XFS_IS_QUOTA_ON(mp) ||
	    ip->i_ino == mp->m_sb.sb_uquotino ||
	    ip->i_ino == mp->m_sb.sb_gquotino)
		return;

	if (tp->t_dqinfo == NULL)
		xfs_trans_alloc_dqinfo(tp);

	if (XFS_IS_UQUOTA_ON(mp) && ip->i_udquot)
		(void) xfs_trans_mod_dquot(tp, ip->i_udquot, field, delta);
	if (XFS_IS_OQUOTA_ON(mp) && ip->i_gdquot)
		(void) xfs_trans_mod_dquot(tp, ip->i_gdquot, field, delta);
}