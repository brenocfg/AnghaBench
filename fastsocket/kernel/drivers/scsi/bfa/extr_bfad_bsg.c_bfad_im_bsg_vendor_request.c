#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct request_queue {int dummy; } ;
struct TYPE_15__ {int payload_len; int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct TYPE_14__ {int /*<<< orphan*/  payload_len; int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct fc_bsg_job {int reply_len; TYPE_8__* reply; int /*<<< orphan*/  (* job_done ) (struct fc_bsg_job*) ;TYPE_7__ reply_payload; TYPE_6__ request_payload; TYPE_5__* req; TYPE_4__* shost; TYPE_3__* request; } ;
struct bfad_s {int dummy; } ;
struct bfad_im_port_s {struct bfad_s* bfad; } ;
struct TYPE_16__ {int reply_payload_rcv_len; int result; } ;
struct TYPE_13__ {struct request_queue* q; } ;
struct TYPE_12__ {scalar_t__* hostdata; } ;
struct TYPE_9__ {int /*<<< orphan*/ * vendor_cmd; } ;
struct TYPE_10__ {TYPE_1__ h_vendor; } ;
struct TYPE_11__ {TYPE_2__ rqst_data; } ;

/* Variables and functions */
 int BFA_STATUS_OK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bfad_iocmd_handler (struct bfad_s*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segments (struct request_queue*,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fc_bsg_job*) ; 

__attribute__((used)) static int
bfad_im_bsg_vendor_request(struct fc_bsg_job *job)
{
	uint32_t vendor_cmd = job->request->rqst_data.h_vendor.vendor_cmd[0];
	struct bfad_im_port_s *im_port =
			(struct bfad_im_port_s *) job->shost->hostdata[0];
	struct bfad_s *bfad = im_port->bfad;
	struct request_queue *request_q = job->req->q;
	void *payload_kbuf;
	int rc = -EINVAL;

	/*
	 * Set the BSG device request_queue size to 256 to support
	 * payloads larger than 512*1024K bytes.
	 */
	blk_queue_max_segments(request_q, 256);

	/* Allocate a temp buffer to hold the passed in user space command */
	payload_kbuf = kzalloc(job->request_payload.payload_len, GFP_KERNEL);
	if (!payload_kbuf) {
		rc = -ENOMEM;
		goto out;
	}

	/* Copy the sg_list passed in to a linear buffer: holds the cmnd data */
	sg_copy_to_buffer(job->request_payload.sg_list,
			  job->request_payload.sg_cnt, payload_kbuf,
			  job->request_payload.payload_len);

	/* Invoke IOCMD handler - to handle all the vendor command requests */
	rc = bfad_iocmd_handler(bfad, vendor_cmd, payload_kbuf,
				job->request_payload.payload_len);
	if (rc != BFA_STATUS_OK)
		goto error;

	/* Copy the response data to the job->reply_payload sg_list */
	sg_copy_from_buffer(job->reply_payload.sg_list,
			    job->reply_payload.sg_cnt,
			    payload_kbuf,
			    job->reply_payload.payload_len);

	/* free the command buffer */
	kfree(payload_kbuf);

	/* Fill the BSG job reply data */
	job->reply_len = job->reply_payload.payload_len;
	job->reply->reply_payload_rcv_len = job->reply_payload.payload_len;
	job->reply->result = rc;

	job->job_done(job);
	return rc;
error:
	/* free the command buffer */
	kfree(payload_kbuf);
out:
	job->reply->result = rc;
	job->reply_len = sizeof(uint32_t);
	job->reply->reply_payload_rcv_len = 0;
	return rc;
}