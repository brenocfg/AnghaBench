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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_16__ {unsigned long handler_data; int /*<<< orphan*/ * wka_port; int /*<<< orphan*/ * completion; int /*<<< orphan*/  handler; int /*<<< orphan*/  resp; int /*<<< orphan*/  req; } ;
struct zfcp_ct_fc_job {TYPE_8__ ct; struct fc_bsg_job* job; } ;
struct zfcp_adapter {TYPE_4__* gs; int /*<<< orphan*/  status; } ;
struct fc_rport {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  sg_list; } ;
struct TYPE_13__ {int /*<<< orphan*/  sg_list; } ;
struct fc_bsg_job {TYPE_7__* req; TYPE_6__ reply_payload; TYPE_5__ request_payload; TYPE_3__* request; struct Scsi_Host* shost; struct fc_rport* rport; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
struct TYPE_15__ {int timeout; } ;
struct TYPE_12__ {int /*<<< orphan*/  ds; int /*<<< orphan*/  ts; int /*<<< orphan*/  ms; int /*<<< orphan*/  as; } ;
struct TYPE_9__ {int preamble_word1; } ;
struct TYPE_10__ {TYPE_1__ r_ct; } ;
struct TYPE_11__ {TYPE_2__ rqst_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  FC_FST_ALIAS 131 
#define  FC_FST_DIR 130 
#define  FC_FST_MGMT 129 
#define  FC_FST_TIME 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct zfcp_ct_fc_job*) ; 
 struct zfcp_ct_fc_job* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* rport_to_shost (struct fc_rport*) ; 
 int /*<<< orphan*/  zfcp_fc_generic_ct_handler ; 
 int zfcp_fc_wka_port_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fc_wka_port_put (int /*<<< orphan*/ *) ; 
 int zfcp_fsf_send_ct (TYPE_8__*,int /*<<< orphan*/ *,int) ; 

int zfcp_fc_execute_ct_fc_job(struct fc_bsg_job *job)
{
	int ret;
	u8 gs_type;
	struct fc_rport *rport = job->rport;
	struct Scsi_Host *shost;
	struct zfcp_adapter *adapter;
	struct zfcp_ct_fc_job *ct_fc_job;
	u32 preamble_word1;

	shost = rport ? rport_to_shost(rport) : job->shost;

	adapter = (struct zfcp_adapter *)shost->hostdata[0];
	if (!(atomic_read(&adapter->status) & ZFCP_STATUS_COMMON_OPEN))
		return -EINVAL;

	ct_fc_job = kzalloc(sizeof(struct zfcp_ct_fc_job), GFP_KERNEL);
	if (!ct_fc_job)
		return -ENOMEM;

	preamble_word1 = job->request->rqst_data.r_ct.preamble_word1;
	gs_type = (preamble_word1 & 0xff000000) >> 24;

	switch (gs_type) {
	case FC_FST_ALIAS:
		ct_fc_job->ct.wka_port = &adapter->gs->as;
		break;
	case FC_FST_MGMT:
		ct_fc_job->ct.wka_port = &adapter->gs->ms;
		break;
	case FC_FST_TIME:
		ct_fc_job->ct.wka_port = &adapter->gs->ts;
		break;
	case FC_FST_DIR:
		ct_fc_job->ct.wka_port = &adapter->gs->ds;
		break;
	default:
		kfree(ct_fc_job);
		return -EINVAL; /* no such service */
	}

	ret = zfcp_fc_wka_port_get(ct_fc_job->ct.wka_port);
	if (ret) {
		kfree(ct_fc_job);
		return ret;
	}

	ct_fc_job->ct.req = job->request_payload.sg_list;
	ct_fc_job->ct.resp = job->reply_payload.sg_list;
	ct_fc_job->ct.handler = zfcp_fc_generic_ct_handler;
	ct_fc_job->ct.handler_data = (unsigned long) ct_fc_job;
	ct_fc_job->ct.completion = NULL;
	ct_fc_job->job = job;

	ret = zfcp_fsf_send_ct(&ct_fc_job->ct, NULL, job->req->timeout / HZ);
	if (ret) {
		kfree(ct_fc_job);
		zfcp_fc_wka_port_put(ct_fc_job->ct.wka_port);
	}
	return ret;
}