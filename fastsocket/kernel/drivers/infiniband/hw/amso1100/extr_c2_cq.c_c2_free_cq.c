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
typedef  int /*<<< orphan*/  wr ;
typedef  union c2wr {int dummy; } c2wr ;
struct TYPE_3__ {unsigned long context; } ;
struct c2wr_cq_destroy_req {int /*<<< orphan*/  cq_handle; int /*<<< orphan*/  rnic_handle; TYPE_1__ hdr; } ;
struct c2wr_cq_destroy_rep {int dummy; } ;
struct c2_vq_req {scalar_t__ reply_msg; } ;
struct c2_dev {int /*<<< orphan*/  adapter_handle; int /*<<< orphan*/  lock; int /*<<< orphan*/ ** qptr_array; } ;
struct TYPE_4__ {size_t index; } ;
struct c2_cq {TYPE_2__ mq; scalar_t__ is_kernel; int /*<<< orphan*/  adapter_handle; int /*<<< orphan*/  refcount; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCWR_CQ_DESTROY ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c2_free_cq_buf (struct c2_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  c2_wr_set_id (struct c2wr_cq_destroy_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct c2wr_cq_destroy_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_repbuf_free (struct c2_dev*,struct c2wr_cq_destroy_rep*) ; 
 struct c2_vq_req* vq_req_alloc (struct c2_dev*) ; 
 int /*<<< orphan*/  vq_req_free (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_get (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_put (struct c2_dev*,struct c2_vq_req*) ; 
 int vq_send_wr (struct c2_dev*,union c2wr*) ; 
 int vq_wait_for_reply (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void c2_free_cq(struct c2_dev *c2dev, struct c2_cq *cq)
{
	int err;
	struct c2_vq_req *vq_req;
	struct c2wr_cq_destroy_req wr;
	struct c2wr_cq_destroy_rep *reply;

	might_sleep();

	/* Clear CQ from the qptr array */
	spin_lock_irq(&c2dev->lock);
	c2dev->qptr_array[cq->mq.index] = NULL;
	atomic_dec(&cq->refcount);
	spin_unlock_irq(&c2dev->lock);

	wait_event(cq->wait, !atomic_read(&cq->refcount));

	vq_req = vq_req_alloc(c2dev);
	if (!vq_req) {
		goto bail0;
	}

	memset(&wr, 0, sizeof(wr));
	c2_wr_set_id(&wr, CCWR_CQ_DESTROY);
	wr.hdr.context = (unsigned long) vq_req;
	wr.rnic_handle = c2dev->adapter_handle;
	wr.cq_handle = cq->adapter_handle;

	vq_req_get(c2dev, vq_req);

	err = vq_send_wr(c2dev, (union c2wr *) & wr);
	if (err) {
		vq_req_put(c2dev, vq_req);
		goto bail1;
	}

	err = vq_wait_for_reply(c2dev, vq_req);
	if (err)
		goto bail1;

	reply = (struct c2wr_cq_destroy_rep *) (unsigned long) (vq_req->reply_msg);
	if (reply)
		vq_repbuf_free(c2dev, reply);
      bail1:
	vq_req_free(c2dev, vq_req);
      bail0:
	if (cq->is_kernel) {
		c2_free_cq_buf(c2dev, &cq->mq);
	}

	return;
}