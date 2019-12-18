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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  tmp ;
struct iw_cm_event {int ird; int ord; int event; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/ * private_data; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  status; } ;
struct c2wr_hdr {scalar_t__ context; } ;
struct c2_vq_req {int event; int /*<<< orphan*/  wait_object; int /*<<< orphan*/  reply_ready; int /*<<< orphan*/  reply_msg; TYPE_1__* cm_id; int /*<<< orphan*/  qp; } ;
struct c2_mq {int msg_size; } ;
struct c2_dev {scalar_t__* qptr_array; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*,struct iw_cm_event*) ;int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  C2_QP_STATE_RTS ; 
 int ENOMEM ; 
#define  IW_CM_EVENT_CLOSE 129 
#define  IW_CM_EVENT_ESTABLISHED 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int c2_errno (void*) ; 
 void* c2_mq_consume (struct c2_mq*) ; 
 int /*<<< orphan*/  c2_mq_free (struct c2_mq*) ; 
 int /*<<< orphan*/  c2_set_qp_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct c2wr_hdr*,void*,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct iw_cm_event*) ; 
 struct c2wr_hdr* vq_repbuf_alloc (struct c2_dev*) ; 
 int /*<<< orphan*/  vq_repbuf_free (struct c2_dev*,struct c2wr_hdr*) ; 
 int /*<<< orphan*/  vq_req_put (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_vq(struct c2_dev *c2dev, u32 mq_index)
{
	void *adapter_msg, *reply_msg;
	struct c2wr_hdr *host_msg;
	struct c2wr_hdr tmp;
	struct c2_mq *reply_vq;
	struct c2_vq_req *req;
	struct iw_cm_event cm_event;
	int err;

	reply_vq = (struct c2_mq *) c2dev->qptr_array[mq_index];

	/*
	 * get next msg from mq_index into adapter_msg.
	 * don't free it yet.
	 */
	adapter_msg = c2_mq_consume(reply_vq);
	if (adapter_msg == NULL) {
		return;
	}

	host_msg = vq_repbuf_alloc(c2dev);

	/*
	 * If we can't get a host buffer, then we'll still
	 * wakeup the waiter, we just won't give him the msg.
	 * It is assumed the waiter will deal with this...
	 */
	if (!host_msg) {
		pr_debug("handle_vq: no repbufs!\n");

		/*
		 * just copy the WR header into a local variable.
		 * this allows us to still demux on the context
		 */
		host_msg = &tmp;
		memcpy(host_msg, adapter_msg, sizeof(tmp));
		reply_msg = NULL;
	} else {
		memcpy(host_msg, adapter_msg, reply_vq->msg_size);
		reply_msg = host_msg;
	}

	/*
	 * consume the msg from the MQ
	 */
	c2_mq_free(reply_vq);

	/*
	 * wakeup the waiter.
	 */
	req = (struct c2_vq_req *) (unsigned long) host_msg->context;
	if (req == NULL) {
		/*
		 * We should never get here, as the adapter should
		 * never send us a reply that we're not expecting.
		 */
		vq_repbuf_free(c2dev, host_msg);
		pr_debug("handle_vq: UNEXPECTEDLY got NULL req\n");
		return;
	}

	if (reply_msg)
		err = c2_errno(reply_msg);
	else
		err = -ENOMEM;

	if (!err) switch (req->event) {
	case IW_CM_EVENT_ESTABLISHED:
		c2_set_qp_state(req->qp,
				C2_QP_STATE_RTS);
		/*
		 * Until ird/ord negotiation via MPAv2 support is added, send
		 * max supported values
		 */
		cm_event.ird = cm_event.ord = 128;
	case IW_CM_EVENT_CLOSE:

		/*
		 * Move the QP to RTS if this is
		 * the established event
		 */
		cm_event.event = req->event;
		cm_event.status = 0;
		cm_event.local_addr = req->cm_id->local_addr;
		cm_event.remote_addr = req->cm_id->remote_addr;
		cm_event.private_data = NULL;
		cm_event.private_data_len = 0;
		req->cm_id->event_handler(req->cm_id, &cm_event);
		break;
	default:
		break;
	}

	req->reply_msg = (u64) (unsigned long) (reply_msg);
	atomic_set(&req->reply_ready, 1);
	wake_up(&req->wait_object);

	/*
	 * If the request was cancelled, then this put will
	 * free the vq_req memory...and reply_msg!!!
	 */
	vq_req_put(c2dev, req);
}