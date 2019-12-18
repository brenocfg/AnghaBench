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
struct zfcp_send_els {scalar_t__ status; } ;
struct zfcp_els_fc_job {struct fc_bsg_job* job; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_2__ ctels_reply; } ;
struct fc_bsg_reply {int /*<<< orphan*/  result; TYPE_3__ reply_data; int /*<<< orphan*/  reply_payload_rcv_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  payload_len; } ;
struct fc_bsg_job {int /*<<< orphan*/  (* job_done ) (struct fc_bsg_job*) ;int /*<<< orphan*/  state_flags; TYPE_1__ reply_payload; struct zfcp_send_els* dd_data; struct fc_bsg_reply* reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FC_CTELS_STATUS_OK ; 
 int /*<<< orphan*/  FC_RQST_STATE_DONE ; 
 int /*<<< orphan*/  kfree (struct zfcp_els_fc_job*) ; 
 int /*<<< orphan*/  stub1 (struct fc_bsg_job*) ; 

__attribute__((used)) static void zfcp_fc_generic_els_handler(unsigned long data)
{
	struct zfcp_els_fc_job *els_fc_job = (struct zfcp_els_fc_job *) data;
	struct fc_bsg_job *job = els_fc_job->job;
	struct fc_bsg_reply *jr = job->reply;
	struct zfcp_send_els *zfcp_els = job->dd_data;

	jr->reply_payload_rcv_len = job->reply_payload.payload_len;
	jr->reply_data.ctels_reply.status = FC_CTELS_STATUS_OK;
	jr->result = zfcp_els->status ? -EIO : 0;
	job->state_flags = FC_RQST_STATE_DONE;
	job->job_done(job);

	kfree(els_fc_job);
}