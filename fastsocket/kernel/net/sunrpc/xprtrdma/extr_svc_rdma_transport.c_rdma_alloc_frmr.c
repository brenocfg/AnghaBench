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
struct svcxprt_rdma {TYPE_1__* sc_cm_id; int /*<<< orphan*/  sc_pd; } ;
struct svc_rdma_fastreg_mr {int /*<<< orphan*/  frmr_list; struct ib_mr* page_list; struct ib_mr* mr; } ;
struct ib_mr {int dummy; } ;
typedef  struct ib_mr ib_fast_reg_page_list ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct svc_rdma_fastreg_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct ib_mr*) ; 
 int /*<<< orphan*/  RPCSVC_MAXPAGES ; 
 struct ib_mr* ib_alloc_fast_reg_mr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ib_mr* ib_alloc_fast_reg_page_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dereg_mr (struct ib_mr*) ; 
 int /*<<< orphan*/  kfree (struct svc_rdma_fastreg_mr*) ; 
 struct svc_rdma_fastreg_mr* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct svc_rdma_fastreg_mr *rdma_alloc_frmr(struct svcxprt_rdma *xprt)
{
	struct ib_mr *mr;
	struct ib_fast_reg_page_list *pl;
	struct svc_rdma_fastreg_mr *frmr;

	frmr = kmalloc(sizeof(*frmr), GFP_KERNEL);
	if (!frmr)
		goto err;

	mr = ib_alloc_fast_reg_mr(xprt->sc_pd, RPCSVC_MAXPAGES);
	if (IS_ERR(mr))
		goto err_free_frmr;

	pl = ib_alloc_fast_reg_page_list(xprt->sc_cm_id->device,
					 RPCSVC_MAXPAGES);
	if (IS_ERR(pl))
		goto err_free_mr;

	frmr->mr = mr;
	frmr->page_list = pl;
	INIT_LIST_HEAD(&frmr->frmr_list);
	return frmr;

 err_free_mr:
	ib_dereg_mr(mr);
 err_free_frmr:
	kfree(frmr);
 err:
	return ERR_PTR(-ENOMEM);
}