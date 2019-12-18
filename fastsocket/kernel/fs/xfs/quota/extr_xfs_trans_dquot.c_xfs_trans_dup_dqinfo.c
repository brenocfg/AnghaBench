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
struct TYPE_8__ {int t_flags; TYPE_1__* t_dqinfo; } ;
typedef  TYPE_2__ xfs_trans_t ;
struct TYPE_9__ {scalar_t__ qt_ino_res_used; scalar_t__ qt_ino_res; scalar_t__ qt_rtblk_res_used; scalar_t__ qt_rtblk_res; scalar_t__ qt_blk_res_used; scalar_t__ qt_blk_res; scalar_t__ qt_rtbcount_delta; scalar_t__ qt_icount_delta; scalar_t__ qt_bcount_delta; int /*<<< orphan*/ * qt_dquot; } ;
typedef  TYPE_3__ xfs_dqtrx_t ;
struct TYPE_7__ {TYPE_3__* dqa_grpdquots; TYPE_3__* dqa_usrdquots; } ;

/* Variables and functions */
 int XFS_QM_TRANS_MAXDQS ; 
 int XFS_TRANS_DQ_DIRTY ; 
 int /*<<< orphan*/  xfs_trans_alloc_dqinfo (TYPE_2__*) ; 

void
xfs_trans_dup_dqinfo(
	xfs_trans_t	*otp,
	xfs_trans_t	*ntp)
{
	xfs_dqtrx_t	*oq, *nq;
	int		i,j;
	xfs_dqtrx_t	*oqa, *nqa;

	if (!otp->t_dqinfo)
		return;

	xfs_trans_alloc_dqinfo(ntp);
	oqa = otp->t_dqinfo->dqa_usrdquots;
	nqa = ntp->t_dqinfo->dqa_usrdquots;

	/*
	 * Because the quota blk reservation is carried forward,
	 * it is also necessary to carry forward the DQ_DIRTY flag.
	 */
	if(otp->t_flags & XFS_TRANS_DQ_DIRTY)
		ntp->t_flags |= XFS_TRANS_DQ_DIRTY;

	for (j = 0; j < 2; j++) {
		for (i = 0; i < XFS_QM_TRANS_MAXDQS; i++) {
			if (oqa[i].qt_dquot == NULL)
				break;
			oq = &oqa[i];
			nq = &nqa[i];

			nq->qt_dquot = oq->qt_dquot;
			nq->qt_bcount_delta = nq->qt_icount_delta = 0;
			nq->qt_rtbcount_delta = 0;

			/*
			 * Transfer whatever is left of the reservations.
			 */
			nq->qt_blk_res = oq->qt_blk_res - oq->qt_blk_res_used;
			oq->qt_blk_res = oq->qt_blk_res_used;

			nq->qt_rtblk_res = oq->qt_rtblk_res -
				oq->qt_rtblk_res_used;
			oq->qt_rtblk_res = oq->qt_rtblk_res_used;

			nq->qt_ino_res = oq->qt_ino_res - oq->qt_ino_res_used;
			oq->qt_ino_res = oq->qt_ino_res_used;

		}
		oqa = otp->t_dqinfo->dqa_grpdquots;
		nqa = ntp->t_dqinfo->dqa_grpdquots;
	}
}