#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct request_queue {int dummy; } ;
struct fc_rport {int dummy; } ;
struct fc_internal {TYPE_4__* f; } ;
struct fc_bsg_rport_els {int dummy; } ;
struct fc_bsg_rport_ct {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  payload_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  payload_len; } ;
struct fc_bsg_job {int request_len; int reply_len; TYPE_5__* reply; TYPE_3__ reply_payload; TYPE_2__ request_payload; TYPE_1__* request; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
typedef  enum fc_dispatch_result { ____Placeholder_fc_dispatch_result } fc_dispatch_result ;
struct TYPE_10__ {int result; scalar_t__ reply_payload_rcv_len; } ;
struct TYPE_9__ {int (* bsg_request ) (struct fc_bsg_job*) ;} ;
struct TYPE_6__ {int msgcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBADR ; 
 int EINVAL ; 
 int ENOMSG ; 
#define  FC_BSG_RPT_CT 129 
#define  FC_BSG_RPT_ELS 128 
 int FC_DISPATCH_UNLOCKED ; 
 int /*<<< orphan*/  fc_bsg_jobdone (struct fc_bsg_job*) ; 
 int stub1 (struct fc_bsg_job*) ; 
 struct fc_internal* to_fc_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum fc_dispatch_result
fc_bsg_rport_dispatch(struct request_queue *q, struct Scsi_Host *shost,
			 struct fc_rport *rport, struct fc_bsg_job *job)
{
	struct fc_internal *i = to_fc_internal(shost->transportt);
	int cmdlen = sizeof(uint32_t);	/* start with length of msgcode */
	int ret;

	/* Validate the rport command */
	switch (job->request->msgcode) {
	case FC_BSG_RPT_ELS:
		cmdlen += sizeof(struct fc_bsg_rport_els);
		goto check_bidi;

	case FC_BSG_RPT_CT:
		cmdlen += sizeof(struct fc_bsg_rport_ct);
check_bidi:
		/* there better be xmt and rcv payloads */
		if ((!job->request_payload.payload_len) ||
		    (!job->reply_payload.payload_len)) {
			ret = -EINVAL;
			goto fail_rport_msg;
		}
		break;
	default:
		ret = -EBADR;
		goto fail_rport_msg;
	}

	/* check if we really have all the request data needed */
	if (job->request_len < cmdlen) {
		ret = -ENOMSG;
		goto fail_rport_msg;
	}

	ret = i->f->bsg_request(job);
	if (!ret)
		return FC_DISPATCH_UNLOCKED;

fail_rport_msg:
	/* return the errno failure code as the only status */
	BUG_ON(job->reply_len < sizeof(uint32_t));
	job->reply->reply_payload_rcv_len = 0;
	job->reply->result = ret;
	job->reply_len = sizeof(uint32_t);
	fc_bsg_jobdone(job);
	return FC_DISPATCH_UNLOCKED;
}