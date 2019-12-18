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
struct svc_rdma_op_ctxt {int count; int /*<<< orphan*/ * pages; struct svcxprt_rdma* xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct svc_rdma_op_ctxt*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rdma_ctxt_cachep ; 

void svc_rdma_put_context(struct svc_rdma_op_ctxt *ctxt, int free_pages)
{
	struct svcxprt_rdma *xprt;
	int i;

	BUG_ON(!ctxt);
	xprt = ctxt->xprt;
	if (free_pages)
		for (i = 0; i < ctxt->count; i++)
			put_page(ctxt->pages[i]);

	kmem_cache_free(svc_rdma_ctxt_cachep, ctxt);
	atomic_dec(&xprt->sc_ctxt_used);
}