#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct p9_trans_rdma {scalar_t__ cm_id; scalar_t__ cq; scalar_t__ pd; scalar_t__ qp; scalar_t__ dma_mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  ib_dealloc_pd (scalar_t__) ; 
 int /*<<< orphan*/  ib_dereg_mr (scalar_t__) ; 
 int /*<<< orphan*/  ib_destroy_cq (scalar_t__) ; 
 int /*<<< orphan*/  ib_destroy_qp (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct p9_trans_rdma*) ; 
 int /*<<< orphan*/  rdma_destroy_id (scalar_t__) ; 

__attribute__((used)) static void rdma_destroy_trans(struct p9_trans_rdma *rdma)
{
	if (!rdma)
		return;

	if (rdma->dma_mr && !IS_ERR(rdma->dma_mr))
		ib_dereg_mr(rdma->dma_mr);

	if (rdma->qp && !IS_ERR(rdma->qp))
		ib_destroy_qp(rdma->qp);

	if (rdma->pd && !IS_ERR(rdma->pd))
		ib_dealloc_pd(rdma->pd);

	if (rdma->cq && !IS_ERR(rdma->cq))
		ib_destroy_cq(rdma->cq);

	if (rdma->cm_id && !IS_ERR(rdma->cm_id))
		rdma_destroy_id(rdma->cm_id);

	kfree(rdma);
}