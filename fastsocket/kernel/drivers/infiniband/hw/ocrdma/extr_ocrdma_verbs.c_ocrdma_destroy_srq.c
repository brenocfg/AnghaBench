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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  len; scalar_t__ pa; } ;
struct ocrdma_srq {struct ocrdma_srq* rqe_wr_id_tbl; struct ocrdma_srq* idx_bit_fields; TYPE_1__ rq; TYPE_2__* pd; struct ocrdma_dev* dev; } ;
struct ocrdma_dev {int dummy; } ;
struct ib_srq {int dummy; } ;
struct TYPE_4__ {scalar_t__ uctx; } ;

/* Variables and functions */
 struct ocrdma_srq* get_ocrdma_srq (struct ib_srq*) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_srq*) ; 
 int /*<<< orphan*/  ocrdma_del_mmap (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocrdma_mbx_destroy_srq (struct ocrdma_dev*,struct ocrdma_srq*) ; 

int ocrdma_destroy_srq(struct ib_srq *ibsrq)
{
	int status;
	struct ocrdma_srq *srq;
	struct ocrdma_dev *dev;

	srq = get_ocrdma_srq(ibsrq);
	dev = srq->dev;

	status = ocrdma_mbx_destroy_srq(dev, srq);

	if (srq->pd->uctx)
		ocrdma_del_mmap(srq->pd->uctx, (u64) srq->rq.pa, srq->rq.len);

	kfree(srq->idx_bit_fields);
	kfree(srq->rqe_wr_id_tbl);
	kfree(srq);
	return status;
}