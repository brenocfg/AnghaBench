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
typedef  int /*<<< orphan*/  u32 ;
struct request {int /*<<< orphan*/  resid_len; } ;
struct fc_rport_priv {int /*<<< orphan*/  e_d_tov; } ;
struct fc_rport {int /*<<< orphan*/  port_id; struct fc_rport_priv* dd_data; } ;
struct TYPE_13__ {struct fc_rport_priv* (* rport_lookup ) (struct fc_lport*,int /*<<< orphan*/ ) ;} ;
struct fc_lport {int /*<<< orphan*/  lp_mutex; int /*<<< orphan*/  e_d_tov; TYPE_5__ tt; struct fc_rport_priv* dns_rdata; } ;
struct TYPE_11__ {int /*<<< orphan*/  payload_len; } ;
struct fc_bsg_job {TYPE_8__* request; struct fc_rport* rport; TYPE_3__ reply_payload; TYPE_2__* reply; struct Scsi_Host* shost; TYPE_1__* req; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_15__ {TYPE_6__ h_els; TYPE_4__ h_ct; } ;
struct TYPE_16__ {int msgcode; TYPE_7__ rqst_data; } ;
struct TYPE_10__ {scalar_t__ reply_payload_rcv_len; } ;
struct TYPE_9__ {struct request* next_rq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FC_BSG_HST_CT 131 
#define  FC_BSG_HST_ELS_NOLOGIN 130 
#define  FC_BSG_RPT_CT 129 
#define  FC_BSG_RPT_ELS 128 
 int /*<<< orphan*/  FC_FID_DIR_SERV ; 
 int fc_lport_ct_request (struct fc_bsg_job*,struct fc_lport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fc_lport_els_request (struct fc_bsg_job*,struct fc_lport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntoh24 (int /*<<< orphan*/ ) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 struct fc_rport_priv* stub1 (struct fc_lport*,int /*<<< orphan*/ ) ; 

int fc_lport_bsg_request(struct fc_bsg_job *job)
{
	struct request *rsp = job->req->next_rq;
	struct Scsi_Host *shost = job->shost;
	struct fc_lport *lport = shost_priv(shost);
	struct fc_rport *rport;
	struct fc_rport_priv *rdata;
	int rc = -EINVAL;
	u32 did;

	job->reply->reply_payload_rcv_len = 0;
	if (rsp)
		rsp->resid_len = job->reply_payload.payload_len;

	mutex_lock(&lport->lp_mutex);

	switch (job->request->msgcode) {
	case FC_BSG_RPT_ELS:
		rport = job->rport;
		if (!rport)
			break;

		rdata = rport->dd_data;
		rc = fc_lport_els_request(job, lport, rport->port_id,
					  rdata->e_d_tov);
		break;

	case FC_BSG_RPT_CT:
		rport = job->rport;
		if (!rport)
			break;

		rdata = rport->dd_data;
		rc = fc_lport_ct_request(job, lport, rport->port_id,
					 rdata->e_d_tov);
		break;

	case FC_BSG_HST_CT:
		did = ntoh24(job->request->rqst_data.h_ct.port_id);
		if (did == FC_FID_DIR_SERV)
			rdata = lport->dns_rdata;
		else
			rdata = lport->tt.rport_lookup(lport, did);

		if (!rdata)
			break;

		rc = fc_lport_ct_request(job, lport, did, rdata->e_d_tov);
		break;

	case FC_BSG_HST_ELS_NOLOGIN:
		did = ntoh24(job->request->rqst_data.h_els.port_id);
		rc = fc_lport_els_request(job, lport, did, lport->e_d_tov);
		break;
	}

	mutex_unlock(&lport->lp_mutex);
	return rc;
}