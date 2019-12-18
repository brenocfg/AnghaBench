#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  d_id; } ;
struct TYPE_4__ {int qlf_len; scalar_t__ qlf_boffset; int /*<<< orphan*/  qlf_blkno; int /*<<< orphan*/  qlf_id; int /*<<< orphan*/  qlf_type; } ;
struct xfs_dq_logitem {TYPE_2__ qli_format; struct xfs_dquot* qli_dquot; int /*<<< orphan*/  qli_item; } ;
struct xfs_dquot {scalar_t__ q_bufoffset; int /*<<< orphan*/  q_blkno; TYPE_1__ q_core; int /*<<< orphan*/  q_mount; struct xfs_dq_logitem q_logitem; } ;
typedef  scalar_t__ __uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_DQUOT ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dquot_item_ops ; 
 int /*<<< orphan*/  xfs_log_item_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
xfs_qm_dquot_logitem_init(
	struct xfs_dquot	*dqp)
{
	struct xfs_dq_logitem	*lp = &dqp->q_logitem;

	xfs_log_item_init(dqp->q_mount, &lp->qli_item, XFS_LI_DQUOT,
					&xfs_dquot_item_ops);
	lp->qli_dquot = dqp;
	lp->qli_format.qlf_type = XFS_LI_DQUOT;
	lp->qli_format.qlf_id = be32_to_cpu(dqp->q_core.d_id);
	lp->qli_format.qlf_blkno = dqp->q_blkno;
	lp->qli_format.qlf_len = 1;
	/*
	 * This is just the offset of this dquot within its buffer
	 * (which is currently 1 FSB and probably won't change).
	 * Hence 32 bits for this offset should be just fine.
	 * Alternatively, we can store (bufoffset / sizeof(xfs_dqblk_t))
	 * here, and recompute it at recovery time.
	 */
	lp->qli_format.qlf_boffset = (__uint32_t)dqp->q_bufoffset;
}