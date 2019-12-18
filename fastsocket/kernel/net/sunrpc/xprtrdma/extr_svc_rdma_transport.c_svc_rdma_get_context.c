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
struct svcxprt_rdma {int /*<<< orphan*/  sc_ctxt_used; } ;
struct svc_rdma_op_ctxt {int /*<<< orphan*/ * frmr; scalar_t__ count; int /*<<< orphan*/  dto_q; struct svcxprt_rdma* xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct svc_rdma_op_ctxt* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rdma_ctxt_cachep ; 

struct svc_rdma_op_ctxt *svc_rdma_get_context(struct svcxprt_rdma *xprt)
{
	struct svc_rdma_op_ctxt *ctxt;

	while (1) {
		ctxt = kmem_cache_alloc(svc_rdma_ctxt_cachep, GFP_KERNEL);
		if (ctxt)
			break;
		schedule_timeout_uninterruptible(msecs_to_jiffies(500));
	}
	ctxt->xprt = xprt;
	INIT_LIST_HEAD(&ctxt->dto_q);
	ctxt->count = 0;
	ctxt->frmr = NULL;
	atomic_inc(&xprt->sc_ctxt_used);
	return ctxt;
}