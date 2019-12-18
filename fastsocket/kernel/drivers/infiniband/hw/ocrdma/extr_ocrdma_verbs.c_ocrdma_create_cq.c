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
typedef  int /*<<< orphan*/  ureq ;
struct ocrdma_dev {struct ocrdma_cq** cq_tbl; } ;
struct ocrdma_create_cq_ureq {scalar_t__ dpp_cq; } ;
struct ib_cq {int dummy; } ;
struct ocrdma_cq {int arm_needed; size_t id; struct ib_cq ibcq; int /*<<< orphan*/  phase; struct ocrdma_dev* dev; int /*<<< orphan*/  rq_head; int /*<<< orphan*/  sq_head; int /*<<< orphan*/  comp_handler_lock; int /*<<< orphan*/  cq_lock; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 struct ib_cq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCRDMA_CQE_VALID ; 
 struct ocrdma_dev* get_ocrdma_dev (struct ib_device*) ; 
 scalar_t__ ib_copy_from_udata (struct ocrdma_create_cq_ureq*,struct ib_udata*,int) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_cq*) ; 
 struct ocrdma_cq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ocrdma_copy_cq_uresp (struct ocrdma_cq*,struct ib_udata*,struct ib_ucontext*) ; 
 int ocrdma_mbx_create_cq (struct ocrdma_dev*,struct ocrdma_cq*,int,scalar_t__) ; 
 int /*<<< orphan*/  ocrdma_mbx_destroy_cq (struct ocrdma_dev*,struct ocrdma_cq*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ib_cq *ocrdma_create_cq(struct ib_device *ibdev, int entries, int vector,
			       struct ib_ucontext *ib_ctx,
			       struct ib_udata *udata)
{
	struct ocrdma_cq *cq;
	struct ocrdma_dev *dev = get_ocrdma_dev(ibdev);
	int status;
	struct ocrdma_create_cq_ureq ureq;

	if (udata) {
		if (ib_copy_from_udata(&ureq, udata, sizeof(ureq)))
			return ERR_PTR(-EFAULT);
	} else
		ureq.dpp_cq = 0;
	cq = kzalloc(sizeof(*cq), GFP_KERNEL);
	if (!cq)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&cq->cq_lock);
	spin_lock_init(&cq->comp_handler_lock);
	INIT_LIST_HEAD(&cq->sq_head);
	INIT_LIST_HEAD(&cq->rq_head);
	cq->dev = dev;

	status = ocrdma_mbx_create_cq(dev, cq, entries, ureq.dpp_cq);
	if (status) {
		kfree(cq);
		return ERR_PTR(status);
	}
	if (ib_ctx) {
		status = ocrdma_copy_cq_uresp(cq, udata, ib_ctx);
		if (status)
			goto ctx_err;
	}
	cq->phase = OCRDMA_CQE_VALID;
	cq->arm_needed = true;
	dev->cq_tbl[cq->id] = cq;

	return &cq->ibcq;

ctx_err:
	ocrdma_mbx_destroy_cq(dev, cq);
	kfree(cq);
	return ERR_PTR(status);
}