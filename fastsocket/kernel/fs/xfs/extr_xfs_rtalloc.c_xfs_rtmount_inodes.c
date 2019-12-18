#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sb_rbmino; scalar_t__ sb_rsumino; } ;
typedef  TYPE_1__ xfs_sb_t ;
struct TYPE_6__ {int /*<<< orphan*/ * m_rsumip; int /*<<< orphan*/ * m_rbmip; TYPE_1__ m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  IRELE (int /*<<< orphan*/ *) ; 
 scalar_t__ NULLFSINO ; 
 int xfs_iget (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int					/* error */
xfs_rtmount_inodes(
	xfs_mount_t	*mp)		/* file system mount structure */
{
	int		error;		/* error return value */
	xfs_sb_t	*sbp;

	sbp = &mp->m_sb;
	if (sbp->sb_rbmino == NULLFSINO)
		return 0;
	error = xfs_iget(mp, NULL, sbp->sb_rbmino, 0, 0, &mp->m_rbmip);
	if (error)
		return error;
	ASSERT(mp->m_rbmip != NULL);
	ASSERT(sbp->sb_rsumino != NULLFSINO);
	error = xfs_iget(mp, NULL, sbp->sb_rsumino, 0, 0, &mp->m_rsumip);
	if (error) {
		IRELE(mp->m_rbmip);
		return error;
	}
	ASSERT(mp->m_rsumip != NULL);
	return 0;
}