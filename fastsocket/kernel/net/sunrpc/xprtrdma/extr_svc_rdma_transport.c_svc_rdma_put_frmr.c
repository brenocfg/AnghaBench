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
struct svcxprt_rdma {int /*<<< orphan*/  sc_frmr_q_lock; int /*<<< orphan*/  sc_frmr_q; } ;
struct svc_rdma_fastreg_mr {int /*<<< orphan*/  frmr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  frmr_unmap_dma (struct svcxprt_rdma*,struct svc_rdma_fastreg_mr*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void svc_rdma_put_frmr(struct svcxprt_rdma *rdma,
		       struct svc_rdma_fastreg_mr *frmr)
{
	if (frmr) {
		frmr_unmap_dma(rdma, frmr);
		spin_lock_bh(&rdma->sc_frmr_q_lock);
		BUG_ON(!list_empty(&frmr->frmr_list));
		list_add(&frmr->frmr_list, &rdma->sc_frmr_q);
		spin_unlock_bh(&rdma->sc_frmr_q_lock);
	}
}