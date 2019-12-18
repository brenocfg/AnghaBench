#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ehca_qp {unsigned int real_qp_num; int /*<<< orphan*/  list_entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct ehca_cq {int /*<<< orphan*/  cq_number; TYPE_1__ ib_cq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/ * qp_hashtab; } ;

/* Variables and functions */
 int QP_HASHTAB_LEN ; 
 int /*<<< orphan*/  ehca_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ehca_cq_assign_qp(struct ehca_cq *cq, struct ehca_qp *qp)
{
	unsigned int qp_num = qp->real_qp_num;
	unsigned int key = qp_num & (QP_HASHTAB_LEN-1);
	unsigned long flags;

	spin_lock_irqsave(&cq->spinlock, flags);
	hlist_add_head(&qp->list_entries, &cq->qp_hashtab[key]);
	spin_unlock_irqrestore(&cq->spinlock, flags);

	ehca_dbg(cq->ib_cq.device, "cq_num=%x real_qp_num=%x",
		 cq->cq_number, qp_num);

	return 0;
}