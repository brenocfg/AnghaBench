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
typedef  union c2wr {int dummy; } c2wr ;
typedef  scalar_t__ u32 ;
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;struct c2_qp* provider_data; int /*<<< orphan*/  (* add_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  device; } ;
struct iw_cm_conn_param {int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; int /*<<< orphan*/  ird; int /*<<< orphan*/  ord; int /*<<< orphan*/  qpn; } ;
struct ib_qp {int dummy; } ;
struct TYPE_4__ {unsigned long context; } ;
struct c2wr_cr_accept_req {scalar_t__ private_data_length; int /*<<< orphan*/ * private_data; int /*<<< orphan*/  qp_handle; scalar_t__ ep_handle; int /*<<< orphan*/  rnic_handle; TYPE_2__ hdr; } ;
struct c2wr_cr_accept_rep {int dummy; } ;
struct c2_vq_req {scalar_t__ reply_msg; int /*<<< orphan*/  event; struct iw_cm_id* cm_id; struct c2_qp* qp; } ;
struct c2_qp {struct iw_cm_id* cm_id; int /*<<< orphan*/  adapter_handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  msg_size; } ;
struct c2_dev {int /*<<< orphan*/  adapter_handle; TYPE_1__ req_vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  C2_MAX_PRIVATE_DATA_SIZE ; 
 int /*<<< orphan*/  C2_QP_STATE_RTS ; 
 int /*<<< orphan*/  CCWR_CR_ACCEPT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IW_CM_EVENT_ESTABLISHED ; 
 int c2_errno (struct c2wr_cr_accept_rep*) ; 
 struct ib_qp* c2_get_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int c2_qp_set_read_limits (struct c2_dev*,struct c2_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2_set_qp_state (struct c2_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2_wr_set_id (struct c2wr_cr_accept_req*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c2wr_cr_accept_req*) ; 
 struct c2wr_cr_accept_req* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 
 int /*<<< orphan*/  stub2 (struct iw_cm_id*) ; 
 struct c2_dev* to_c2dev (int /*<<< orphan*/ ) ; 
 struct c2_qp* to_c2qp (struct ib_qp*) ; 
 int /*<<< orphan*/  vq_repbuf_free (struct c2_dev*,struct c2wr_cr_accept_rep*) ; 
 struct c2_vq_req* vq_req_alloc (struct c2_dev*) ; 
 int /*<<< orphan*/  vq_req_free (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_get (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_put (struct c2_dev*,struct c2_vq_req*) ; 
 int vq_send_wr (struct c2_dev*,union c2wr*) ; 
 int vq_wait_for_reply (struct c2_dev*,struct c2_vq_req*) ; 

int c2_llp_accept(struct iw_cm_id *cm_id, struct iw_cm_conn_param *iw_param)
{
	struct c2_dev *c2dev = to_c2dev(cm_id->device);
	struct c2_qp *qp;
	struct ib_qp *ibqp;
	struct c2wr_cr_accept_req *wr;	/* variable length WR */
	struct c2_vq_req *vq_req;
	struct c2wr_cr_accept_rep *reply;	/* VQ Reply msg ptr. */
	int err;

	ibqp = c2_get_qp(cm_id->device, iw_param->qpn);
	if (!ibqp)
		return -EINVAL;
	qp = to_c2qp(ibqp);

	/* Set the RDMA read limits */
	err = c2_qp_set_read_limits(c2dev, qp, iw_param->ord, iw_param->ird);
	if (err)
		goto bail0;

	/* Allocate verbs request. */
	vq_req = vq_req_alloc(c2dev);
	if (!vq_req) {
		err = -ENOMEM;
		goto bail0;
	}
	vq_req->qp = qp;
	vq_req->cm_id = cm_id;
	vq_req->event = IW_CM_EVENT_ESTABLISHED;

	wr = kmalloc(c2dev->req_vq.msg_size, GFP_KERNEL);
	if (!wr) {
		err = -ENOMEM;
		goto bail1;
	}

	/* Build the WR */
	c2_wr_set_id(wr, CCWR_CR_ACCEPT);
	wr->hdr.context = (unsigned long) vq_req;
	wr->rnic_handle = c2dev->adapter_handle;
	wr->ep_handle = (u32) (unsigned long) cm_id->provider_data;
	wr->qp_handle = qp->adapter_handle;

	/* Replace the cr_handle with the QP after accept */
	cm_id->provider_data = qp;
	cm_id->add_ref(cm_id);
	qp->cm_id = cm_id;

	cm_id->provider_data = qp;

	/* Validate private_data length */
	if (iw_param->private_data_len > C2_MAX_PRIVATE_DATA_SIZE) {
		err = -EINVAL;
		goto bail1;
	}

	if (iw_param->private_data) {
		wr->private_data_length = cpu_to_be32(iw_param->private_data_len);
		memcpy(&wr->private_data[0],
		       iw_param->private_data, iw_param->private_data_len);
	} else
		wr->private_data_length = 0;

	/* Reference the request struct.  Dereferenced in the int handler. */
	vq_req_get(c2dev, vq_req);

	/* Send WR to adapter */
	err = vq_send_wr(c2dev, (union c2wr *) wr);
	if (err) {
		vq_req_put(c2dev, vq_req);
		goto bail1;
	}

	/* Wait for reply from adapter */
	err = vq_wait_for_reply(c2dev, vq_req);
	if (err)
		goto bail1;

	/* Check that reply is present */
	reply = (struct c2wr_cr_accept_rep *) (unsigned long) vq_req->reply_msg;
	if (!reply) {
		err = -ENOMEM;
		goto bail1;
	}

	err = c2_errno(reply);
	vq_repbuf_free(c2dev, reply);

	if (!err)
		c2_set_qp_state(qp, C2_QP_STATE_RTS);
 bail1:
	kfree(wr);
	vq_req_free(c2dev, vq_req);
 bail0:
	if (err) {
		/*
		 * If we fail, release reference on QP and
		 * disassociate QP from CM_ID
		 */
		cm_id->provider_data = NULL;
		qp->cm_id = NULL;
		cm_id->rem_ref(cm_id);
	}
	return err;
}