#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union c2wr {int dummy; } c2wr ;
typedef  void* u64 ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; } ;
struct iw_cm_id {void* provider_data; TYPE_3__ local_addr; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {void* context; } ;
struct c2wr_ep_listen_create_req {void* user_context; int /*<<< orphan*/  backlog; int /*<<< orphan*/  local_port; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  rnic_handle; TYPE_1__ hdr; } ;
struct c2wr_ep_listen_create_rep {scalar_t__ ep_handle; } ;
struct c2_vq_req {scalar_t__ reply_msg; } ;
struct c2_dev {int /*<<< orphan*/  adapter_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCWR_EP_LISTEN_CREATE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int c2_errno (struct c2wr_ep_listen_create_rep*) ; 
 int /*<<< orphan*/  c2_wr_set_id (struct c2wr_ep_listen_create_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct c2_dev* to_c2dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_repbuf_free (struct c2_dev*,struct c2wr_ep_listen_create_rep*) ; 
 struct c2_vq_req* vq_req_alloc (struct c2_dev*) ; 
 int /*<<< orphan*/  vq_req_free (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_get (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_put (struct c2_dev*,struct c2_vq_req*) ; 
 int vq_send_wr (struct c2_dev*,union c2wr*) ; 
 int vq_wait_for_reply (struct c2_dev*,struct c2_vq_req*) ; 

int c2_llp_service_create(struct iw_cm_id *cm_id, int backlog)
{
	struct c2_dev *c2dev;
	struct c2wr_ep_listen_create_req wr;
	struct c2wr_ep_listen_create_rep *reply;
	struct c2_vq_req *vq_req;
	int err;

	c2dev = to_c2dev(cm_id->device);
	if (c2dev == NULL)
		return -EINVAL;

	/*
	 * Allocate verbs request.
	 */
	vq_req = vq_req_alloc(c2dev);
	if (!vq_req)
		return -ENOMEM;

	/*
	 * Build the WR
	 */
	c2_wr_set_id(&wr, CCWR_EP_LISTEN_CREATE);
	wr.hdr.context = (u64) (unsigned long) vq_req;
	wr.rnic_handle = c2dev->adapter_handle;
	wr.local_addr = cm_id->local_addr.sin_addr.s_addr;
	wr.local_port = cm_id->local_addr.sin_port;
	wr.backlog = cpu_to_be32(backlog);
	wr.user_context = (u64) (unsigned long) cm_id;

	/*
	 * Reference the request struct.  Dereferenced in the int handler.
	 */
	vq_req_get(c2dev, vq_req);

	/*
	 * Send WR to adapter
	 */
	err = vq_send_wr(c2dev, (union c2wr *) & wr);
	if (err) {
		vq_req_put(c2dev, vq_req);
		goto bail0;
	}

	/*
	 * Wait for reply from adapter
	 */
	err = vq_wait_for_reply(c2dev, vq_req);
	if (err)
		goto bail0;

	/*
	 * Process reply
	 */
	reply =
	    (struct c2wr_ep_listen_create_rep *) (unsigned long) vq_req->reply_msg;
	if (!reply) {
		err = -ENOMEM;
		goto bail1;
	}

	if ((err = c2_errno(reply)) != 0)
		goto bail1;

	/*
	 * Keep the adapter handle. Used in subsequent destroy
	 */
	cm_id->provider_data = (void*)(unsigned long) reply->ep_handle;

	/*
	 * free vq stuff
	 */
	vq_repbuf_free(c2dev, reply);
	vq_req_free(c2dev, vq_req);

	return 0;

 bail1:
	vq_repbuf_free(c2dev, reply);
 bail0:
	vq_req_free(c2dev, vq_req);
	return err;
}