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
struct fc_internal {TYPE_7__* f; } ;
struct TYPE_10__ {int /*<<< orphan*/  payload_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  payload_len; } ;
struct fc_bsg_job {int request_len; int reply_len; TYPE_8__* reply; TYPE_5__* request; TYPE_2__ reply_payload; TYPE_1__ request_payload; } ;
struct fc_bsg_host_vendor {int dummy; } ;
struct fc_bsg_host_els {int dummy; } ;
struct fc_bsg_host_del_rport {int dummy; } ;
struct fc_bsg_host_ct {int dummy; } ;
struct fc_bsg_host_add_rport {int dummy; } ;
struct Scsi_Host {TYPE_6__* hostt; int /*<<< orphan*/  transportt; } ;
typedef  enum fc_dispatch_result { ____Placeholder_fc_dispatch_result } fc_dispatch_result ;
struct TYPE_16__ {int result; scalar_t__ reply_payload_rcv_len; } ;
struct TYPE_15__ {int (* bsg_request ) (struct fc_bsg_job*) ;} ;
struct TYPE_14__ {long vendor_id; } ;
struct TYPE_11__ {long vendor_id; } ;
struct TYPE_12__ {TYPE_3__ h_vendor; } ;
struct TYPE_13__ {int msgcode; TYPE_4__ rqst_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBADR ; 
 int EINVAL ; 
 int ENOMSG ; 
 int ESRCH ; 
#define  FC_BSG_HST_ADD_RPORT 132 
#define  FC_BSG_HST_CT 131 
#define  FC_BSG_HST_DEL_RPORT 130 
#define  FC_BSG_HST_ELS_NOLOGIN 129 
#define  FC_BSG_HST_VENDOR 128 
 int FC_DISPATCH_UNLOCKED ; 
 int /*<<< orphan*/  fc_bsg_jobdone (struct fc_bsg_job*) ; 
 int stub1 (struct fc_bsg_job*) ; 
 struct fc_internal* to_fc_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum fc_dispatch_result
fc_bsg_host_dispatch(struct request_queue *q, struct Scsi_Host *shost,
			 struct fc_bsg_job *job)
{
	struct fc_internal *i = to_fc_internal(shost->transportt);
	int cmdlen = sizeof(uint32_t);	/* start with length of msgcode */
	int ret;

	/* Validate the host command */
	switch (job->request->msgcode) {
	case FC_BSG_HST_ADD_RPORT:
		cmdlen += sizeof(struct fc_bsg_host_add_rport);
		break;

	case FC_BSG_HST_DEL_RPORT:
		cmdlen += sizeof(struct fc_bsg_host_del_rport);
		break;

	case FC_BSG_HST_ELS_NOLOGIN:
		cmdlen += sizeof(struct fc_bsg_host_els);
		/* there better be a xmt and rcv payloads */
		if ((!job->request_payload.payload_len) ||
		    (!job->reply_payload.payload_len)) {
			ret = -EINVAL;
			goto fail_host_msg;
		}
		break;

	case FC_BSG_HST_CT:
		cmdlen += sizeof(struct fc_bsg_host_ct);
		/* there better be xmt and rcv payloads */
		if ((!job->request_payload.payload_len) ||
		    (!job->reply_payload.payload_len)) {
			ret = -EINVAL;
			goto fail_host_msg;
		}
		break;

	case FC_BSG_HST_VENDOR:
		cmdlen += sizeof(struct fc_bsg_host_vendor);
		if ((shost->hostt->vendor_id == 0L) ||
		    (job->request->rqst_data.h_vendor.vendor_id !=
			shost->hostt->vendor_id)) {
			ret = -ESRCH;
			goto fail_host_msg;
		}
		break;

	default:
		ret = -EBADR;
		goto fail_host_msg;
	}

	/* check if we really have all the request data needed */
	if (job->request_len < cmdlen) {
		ret = -ENOMSG;
		goto fail_host_msg;
	}

	ret = i->f->bsg_request(job);
	if (!ret)
		return FC_DISPATCH_UNLOCKED;

fail_host_msg:
	/* return the errno failure code as the only status */
	BUG_ON(job->reply_len < sizeof(uint32_t));
	job->reply->reply_payload_rcv_len = 0;
	job->reply->result = ret;
	job->reply_len = sizeof(uint32_t);
	fc_bsg_jobdone(job);
	return FC_DISPATCH_UNLOCKED;
}