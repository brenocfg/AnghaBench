#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocrdma_pd {int /*<<< orphan*/  id; struct ocrdma_dev* dev; } ;
struct TYPE_9__ {int remote_wr; int remote_rd; int local_wr; int local_rd; int remote_atomic; int /*<<< orphan*/  lkey; void* len; void* va; int /*<<< orphan*/  fbo; int /*<<< orphan*/  pbe_size; struct ocrdma_dev* dev; } ;
struct ib_mr {int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; } ;
struct ocrdma_mr {TYPE_2__ hwmr; struct ib_mr ibmr; struct ocrdma_pd* pd; TYPE_5__* umem; } ;
struct ocrdma_dev {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {TYPE_1__* uobject; } ;
struct TYPE_10__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  page_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 scalar_t__ IS_ERR (TYPE_5__*) ; 
 int /*<<< orphan*/  build_user_pbes (struct ocrdma_dev*,struct ocrdma_mr*,int /*<<< orphan*/ ) ; 
 struct ocrdma_pd* get_ocrdma_pd (struct ib_pd*) ; 
 TYPE_5__* ib_umem_get (int /*<<< orphan*/ ,void*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_page_count (TYPE_5__*) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_mr*) ; 
 struct ocrdma_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ocrdma_build_pbl_tbl (struct ocrdma_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocrdma_free_mr_pbl_tbl (struct ocrdma_dev*,TYPE_2__*) ; 
 int ocrdma_get_pbl_info (struct ocrdma_mr*,int /*<<< orphan*/ ) ; 
 int ocrdma_reg_mr (struct ocrdma_dev*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

struct ib_mr *ocrdma_reg_user_mr(struct ib_pd *ibpd, u64 start, u64 len,
				 u64 usr_addr, int acc, struct ib_udata *udata)
{
	int status = -ENOMEM;
	struct ocrdma_dev *dev;
	struct ocrdma_mr *mr;
	struct ocrdma_pd *pd;
	u32 num_pbes;

	pd = get_ocrdma_pd(ibpd);
	dev = pd->dev;

	if (acc & IB_ACCESS_REMOTE_WRITE && !(acc & IB_ACCESS_LOCAL_WRITE))
		return ERR_PTR(-EINVAL);

	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr)
		return ERR_PTR(status);
	mr->hwmr.dev = dev;
	mr->umem = ib_umem_get(ibpd->uobject->context, start, len, acc, 0);
	if (IS_ERR(mr->umem)) {
		status = -EFAULT;
		goto umem_err;
	}
	num_pbes = ib_umem_page_count(mr->umem);
	status = ocrdma_get_pbl_info(mr, num_pbes);
	if (status)
		goto umem_err;

	mr->hwmr.pbe_size = mr->umem->page_size;
	mr->hwmr.fbo = mr->umem->offset;
	mr->hwmr.va = usr_addr;
	mr->hwmr.len = len;
	mr->hwmr.remote_wr = (acc & IB_ACCESS_REMOTE_WRITE) ? 1 : 0;
	mr->hwmr.remote_rd = (acc & IB_ACCESS_REMOTE_READ) ? 1 : 0;
	mr->hwmr.local_wr = (acc & IB_ACCESS_LOCAL_WRITE) ? 1 : 0;
	mr->hwmr.local_rd = 1;
	mr->hwmr.remote_atomic = (acc & IB_ACCESS_REMOTE_ATOMIC) ? 1 : 0;
	status = ocrdma_build_pbl_tbl(dev, &mr->hwmr);
	if (status)
		goto umem_err;
	build_user_pbes(dev, mr, num_pbes);
	status = ocrdma_reg_mr(dev, &mr->hwmr, pd->id, acc);
	if (status)
		goto mbx_err;
	mr->pd = pd;
	mr->ibmr.lkey = mr->hwmr.lkey;
	if (mr->hwmr.remote_wr || mr->hwmr.remote_rd)
		mr->ibmr.rkey = mr->hwmr.lkey;

	return &mr->ibmr;

mbx_err:
	ocrdma_free_mr_pbl_tbl(dev, &mr->hwmr);
umem_err:
	kfree(mr);
	return ERR_PTR(status);
}