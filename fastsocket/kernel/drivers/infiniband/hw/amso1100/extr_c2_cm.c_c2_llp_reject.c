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
typedef  union c2wr {int dummy; } c2wr ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct iw_cm_id {scalar_t__ provider_data; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {unsigned long context; } ;
struct c2wr_cr_reject_req {scalar_t__ ep_handle; int /*<<< orphan*/  rnic_handle; TYPE_1__ hdr; } ;
struct c2wr_cr_reject_rep {int dummy; } ;
struct c2_vq_req {scalar_t__ reply_msg; } ;
struct c2_dev {int /*<<< orphan*/  adapter_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCWR_CR_REJECT ; 
 int ENOMEM ; 
 int c2_errno (struct c2wr_cr_reject_rep*) ; 
 int /*<<< orphan*/  c2_wr_set_id (struct c2wr_cr_reject_req*,int /*<<< orphan*/ ) ; 
 struct c2_dev* to_c2dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_repbuf_free (struct c2_dev*,struct c2wr_cr_reject_rep*) ; 
 struct c2_vq_req* vq_req_alloc (struct c2_dev*) ; 
 int /*<<< orphan*/  vq_req_free (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_get (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_put (struct c2_dev*,struct c2_vq_req*) ; 
 int vq_send_wr (struct c2_dev*,union c2wr*) ; 
 int vq_wait_for_reply (struct c2_dev*,struct c2_vq_req*) ; 

int c2_llp_reject(struct iw_cm_id *cm_id, const void *pdata, u8 pdata_len)
{
	struct c2_dev *c2dev;
	struct c2wr_cr_reject_req wr;
	struct c2_vq_req *vq_req;
	struct c2wr_cr_reject_rep *reply;
	int err;

	c2dev = to_c2dev(cm_id->device);

	/*
	 * Allocate verbs request.
	 */
	vq_req = vq_req_alloc(c2dev);
	if (!vq_req)
		return -ENOMEM;

	/*
	 * Build the WR
	 */
	c2_wr_set_id(&wr, CCWR_CR_REJECT);
	wr.hdr.context = (unsigned long) vq_req;
	wr.rnic_handle = c2dev->adapter_handle;
	wr.ep_handle = (u32) (unsigned long) cm_id->provider_data;

	/*
	 * reference the request struct.  dereferenced in the int handler.
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
	reply = (struct c2wr_cr_reject_rep *) (unsigned long)
		vq_req->reply_msg;
	if (!reply) {
		err = -ENOMEM;
		goto bail0;
	}
	err = c2_errno(reply);
	/*
	 * free vq stuff
	 */
	vq_repbuf_free(c2dev, reply);

 bail0:
	vq_req_free(c2dev, vq_req);
	return err;
}