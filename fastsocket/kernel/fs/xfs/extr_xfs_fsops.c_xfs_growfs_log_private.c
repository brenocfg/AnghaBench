#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sb_logblocks; scalar_t__ sb_logstart; } ;
struct TYPE_8__ {TYPE_1__ m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_9__ {scalar_t__ newblocks; int isint; } ;
typedef  TYPE_3__ xfs_growfs_log_t ;
typedef  scalar_t__ xfs_extlen_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSYS ; 
 scalar_t__ XFS_B_TO_FSB (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_MIN_LOG_BLOCKS ; 
 int /*<<< orphan*/  XFS_MIN_LOG_BYTES ; 

__attribute__((used)) static int
xfs_growfs_log_private(
	xfs_mount_t		*mp,	/* mount point for filesystem */
	xfs_growfs_log_t	*in)	/* growfs log input struct */
{
	xfs_extlen_t		nb;

	nb = in->newblocks;
	if (nb < XFS_MIN_LOG_BLOCKS || nb < XFS_B_TO_FSB(mp, XFS_MIN_LOG_BYTES))
		return XFS_ERROR(EINVAL);
	if (nb == mp->m_sb.sb_logblocks &&
	    in->isint == (mp->m_sb.sb_logstart != 0))
		return XFS_ERROR(EINVAL);
	/*
	 * Moving the log is hard, need new interfaces to sync
	 * the log first, hold off all activity while moving it.
	 * Can have shorter or longer log in the same space,
	 * or transform internal to external log or vice versa.
	 */
	return XFS_ERROR(ENOSYS);
}