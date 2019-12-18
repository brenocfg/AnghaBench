#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mthca_ucontext {int /*<<< orphan*/  db_tab; int /*<<< orphan*/  uar; } ;
struct mthca_sqp {int dummy; } ;
struct ib_qp {int qp_num; } ;
struct TYPE_12__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  max; int /*<<< orphan*/  db_index; } ;
struct TYPE_11__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  max; int /*<<< orphan*/  db_index; } ;
struct TYPE_8__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_9__ {TYPE_1__ ibmr; } ;
struct mthca_qp {int qpn; struct ib_qp ibqp; int /*<<< orphan*/  max_inline_data; TYPE_5__ rq; TYPE_4__ sq; TYPE_2__ mr; } ;
struct mthca_create_qp {int /*<<< orphan*/  rq_db_index; int /*<<< orphan*/  sq_db_index; int /*<<< orphan*/  lkey; int /*<<< orphan*/  rq_db_page; int /*<<< orphan*/  sq_db_page; } ;
struct ib_udata {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_init_attr {int qp_type; TYPE_6__ cap; int /*<<< orphan*/  port_num; int /*<<< orphan*/  sq_sig_type; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; scalar_t__ create_flags; } ;
struct ib_pd {int /*<<< orphan*/  device; TYPE_3__* uobject; } ;
struct TYPE_10__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 struct ib_qp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 int /*<<< orphan*/  ib_copy_from_udata (struct mthca_create_qp*,struct ib_udata*,int) ; 
 int /*<<< orphan*/  kfree (struct mthca_qp*) ; 
 struct mthca_qp* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mthca_alloc_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_6__*,struct mthca_qp*) ; 
 int mthca_alloc_sqp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mthca_map_user_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_unmap_user_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mcq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mpd (struct ib_pd*) ; 
 int /*<<< orphan*/  to_msqp (struct mthca_qp*) ; 
 struct mthca_ucontext* to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_qp *mthca_create_qp(struct ib_pd *pd,
				     struct ib_qp_init_attr *init_attr,
				     struct ib_udata *udata)
{
	struct mthca_create_qp ucmd;
	struct mthca_qp *qp;
	int err;

	if (init_attr->create_flags)
		return ERR_PTR(-EINVAL);

	switch (init_attr->qp_type) {
	case IB_QPT_RC:
	case IB_QPT_UC:
	case IB_QPT_UD:
	{
		struct mthca_ucontext *context;

		qp = kmalloc(sizeof *qp, GFP_KERNEL);
		if (!qp)
			return ERR_PTR(-ENOMEM);

		if (pd->uobject) {
			context = to_mucontext(pd->uobject->context);

			if (ib_copy_from_udata(&ucmd, udata, sizeof ucmd)) {
				kfree(qp);
				return ERR_PTR(-EFAULT);
			}

			err = mthca_map_user_db(to_mdev(pd->device), &context->uar,
						context->db_tab,
						ucmd.sq_db_index, ucmd.sq_db_page);
			if (err) {
				kfree(qp);
				return ERR_PTR(err);
			}

			err = mthca_map_user_db(to_mdev(pd->device), &context->uar,
						context->db_tab,
						ucmd.rq_db_index, ucmd.rq_db_page);
			if (err) {
				mthca_unmap_user_db(to_mdev(pd->device),
						    &context->uar,
						    context->db_tab,
						    ucmd.sq_db_index);
				kfree(qp);
				return ERR_PTR(err);
			}

			qp->mr.ibmr.lkey = ucmd.lkey;
			qp->sq.db_index  = ucmd.sq_db_index;
			qp->rq.db_index  = ucmd.rq_db_index;
		}

		err = mthca_alloc_qp(to_mdev(pd->device), to_mpd(pd),
				     to_mcq(init_attr->send_cq),
				     to_mcq(init_attr->recv_cq),
				     init_attr->qp_type, init_attr->sq_sig_type,
				     &init_attr->cap, qp);

		if (err && pd->uobject) {
			context = to_mucontext(pd->uobject->context);

			mthca_unmap_user_db(to_mdev(pd->device),
					    &context->uar,
					    context->db_tab,
					    ucmd.sq_db_index);
			mthca_unmap_user_db(to_mdev(pd->device),
					    &context->uar,
					    context->db_tab,
					    ucmd.rq_db_index);
		}

		qp->ibqp.qp_num = qp->qpn;
		break;
	}
	case IB_QPT_SMI:
	case IB_QPT_GSI:
	{
		/* Don't allow userspace to create special QPs */
		if (pd->uobject)
			return ERR_PTR(-EINVAL);

		qp = kmalloc(sizeof (struct mthca_sqp), GFP_KERNEL);
		if (!qp)
			return ERR_PTR(-ENOMEM);

		qp->ibqp.qp_num = init_attr->qp_type == IB_QPT_SMI ? 0 : 1;

		err = mthca_alloc_sqp(to_mdev(pd->device), to_mpd(pd),
				      to_mcq(init_attr->send_cq),
				      to_mcq(init_attr->recv_cq),
				      init_attr->sq_sig_type, &init_attr->cap,
				      qp->ibqp.qp_num, init_attr->port_num,
				      to_msqp(qp));
		break;
	}
	default:
		/* Don't support raw QPs */
		return ERR_PTR(-ENOSYS);
	}

	if (err) {
		kfree(qp);
		return ERR_PTR(err);
	}

	init_attr->cap.max_send_wr     = qp->sq.max;
	init_attr->cap.max_recv_wr     = qp->rq.max;
	init_attr->cap.max_send_sge    = qp->sq.max_gs;
	init_attr->cap.max_recv_sge    = qp->rq.max_gs;
	init_attr->cap.max_inline_data = qp->max_inline_data;

	return &qp->ibqp;
}