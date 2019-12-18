#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ib_srq {int dummy; } ;
struct TYPE_7__ {int max_cnt; } ;
struct ocrdma_srq {int bit_fields_len; struct ocrdma_srq* idx_bit_fields; struct ocrdma_srq* rqe_wr_id_tbl; struct ib_srq ibsrq; TYPE_3__ rq; scalar_t__ db; struct ocrdma_pd* pd; struct ocrdma_dev* dev; int /*<<< orphan*/  q_lock; } ;
struct ocrdma_pd {int id; struct ocrdma_dev* dev; } ;
struct TYPE_6__ {int db_page_size; scalar_t__ db; } ;
struct TYPE_5__ {scalar_t__ max_recv_sge; scalar_t__ max_rqe; } ;
struct ocrdma_dev {TYPE_2__ nic_info; TYPE_1__ attr; } ;
struct ib_udata {int dummy; } ;
struct TYPE_8__ {scalar_t__ max_sge; scalar_t__ max_wr; scalar_t__ srq_limit; } ;
struct ib_srq_init_attr {TYPE_4__ attr; } ;
struct ib_pd {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_srq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ocrdma_pd* get_ocrdma_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_srq*) ; 
 struct ocrdma_srq* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocrdma_srq*,int,int) ; 
 int ocrdma_copy_srq_uresp (struct ocrdma_srq*,struct ib_udata*) ; 
 int ocrdma_mbx_create_srq (struct ocrdma_srq*,struct ib_srq_init_attr*,struct ocrdma_pd*) ; 
 int /*<<< orphan*/  ocrdma_mbx_destroy_srq (struct ocrdma_dev*,struct ocrdma_srq*) ; 
 int ocrdma_mbx_modify_srq (struct ocrdma_srq*,TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ib_srq *ocrdma_create_srq(struct ib_pd *ibpd,
				 struct ib_srq_init_attr *init_attr,
				 struct ib_udata *udata)
{
	int status = -ENOMEM;
	struct ocrdma_pd *pd = get_ocrdma_pd(ibpd);
	struct ocrdma_dev *dev = pd->dev;
	struct ocrdma_srq *srq;

	if (init_attr->attr.max_sge > dev->attr.max_recv_sge)
		return ERR_PTR(-EINVAL);
	if (init_attr->attr.max_wr > dev->attr.max_rqe)
		return ERR_PTR(-EINVAL);

	srq = kzalloc(sizeof(*srq), GFP_KERNEL);
	if (!srq)
		return ERR_PTR(status);

	spin_lock_init(&srq->q_lock);
	srq->dev = dev;
	srq->pd = pd;
	srq->db = dev->nic_info.db + (pd->id * dev->nic_info.db_page_size);
	status = ocrdma_mbx_create_srq(srq, init_attr, pd);
	if (status)
		goto err;

	if (udata == NULL) {
		srq->rqe_wr_id_tbl = kzalloc(sizeof(u64) * srq->rq.max_cnt,
			    GFP_KERNEL);
		if (srq->rqe_wr_id_tbl == NULL)
			goto arm_err;

		srq->bit_fields_len = (srq->rq.max_cnt / 32) +
		    (srq->rq.max_cnt % 32 ? 1 : 0);
		srq->idx_bit_fields =
		    kmalloc(srq->bit_fields_len * sizeof(u32), GFP_KERNEL);
		if (srq->idx_bit_fields == NULL)
			goto arm_err;
		memset(srq->idx_bit_fields, 0xff,
		       srq->bit_fields_len * sizeof(u32));
	}

	if (init_attr->attr.srq_limit) {
		status = ocrdma_mbx_modify_srq(srq, &init_attr->attr);
		if (status)
			goto arm_err;
	}

	if (udata) {
		status = ocrdma_copy_srq_uresp(srq, udata);
		if (status)
			goto arm_err;
	}

	return &srq->ibsrq;

arm_err:
	ocrdma_mbx_destroy_srq(dev, srq);
err:
	kfree(srq->rqe_wr_id_tbl);
	kfree(srq->idx_bit_fields);
	kfree(srq);
	return ERR_PTR(status);
}