#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct req_que {int num_outstanding_cmds; TYPE_6__** outstanding_cmds; } ;
struct qla_hw_data {int max_req_queues; int /*<<< orphan*/  hardware_lock; TYPE_2__* isp_ops; struct req_que** req_q_map; } ;
struct fc_bsg_job {TYPE_5__* request; TYPE_4__* reply; TYPE_3__* req; int /*<<< orphan*/  shost; } ;
struct TYPE_14__ {struct fc_bsg_job* bsg_job; } ;
struct TYPE_19__ {scalar_t__ type; int /*<<< orphan*/  fcport; TYPE_1__ u; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_20__ {struct qla_hw_data* hw; } ;
typedef  TYPE_7__ scsi_qla_host_t ;
struct TYPE_18__ {scalar_t__ msgcode; } ;
struct TYPE_17__ {int /*<<< orphan*/  result; } ;
struct TYPE_16__ {int /*<<< orphan*/  errors; } ;
struct TYPE_15__ {scalar_t__ (* abort_command ) (TYPE_6__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ FC_BSG_HST_CT ; 
 scalar_t__ SRB_CT_CMD ; 
 scalar_t__ SRB_ELS_CMD_HST ; 
 scalar_t__ SRB_FXIOCB_BCMD ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_7__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_user ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_7__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla2x00_rel_sp (TYPE_7__*,TYPE_6__*) ; 
 TYPE_7__* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (TYPE_6__*) ; 

int
qla24xx_bsg_timeout(struct fc_bsg_job *bsg_job)
{
	scsi_qla_host_t *vha = shost_priv(bsg_job->shost);
	struct qla_hw_data *ha = vha->hw;
	srb_t *sp;
	int cnt, que;
	unsigned long flags;
	struct req_que *req;

	/* find the bsg job from the active list of commands */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	for (que = 0; que < ha->max_req_queues; que++) {
		req = ha->req_q_map[que];
		if (!req)
			continue;

		for (cnt = 1; cnt < req->num_outstanding_cmds; cnt++) {
			sp = req->outstanding_cmds[cnt];
			if (sp) {
				if (((sp->type == SRB_CT_CMD) ||
					(sp->type == SRB_ELS_CMD_HST) ||
					(sp->type == SRB_FXIOCB_BCMD))
					&& (sp->u.bsg_job == bsg_job)) {
					spin_unlock_irqrestore(&ha->hardware_lock, flags);
					if (ha->isp_ops->abort_command(sp)) {
						ql_log(ql_log_warn, vha, 0x7089,
						    "mbx abort_command "
						    "failed.\n");
						bsg_job->req->errors =
						bsg_job->reply->result = -EIO;
					} else {
						ql_dbg(ql_dbg_user, vha, 0x708a,
						    "mbx abort_command "
						    "success.\n");
						bsg_job->req->errors =
						bsg_job->reply->result = 0;
					}
					spin_lock_irqsave(&ha->hardware_lock, flags);
					goto done;
				}
			}
		}
	}
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	ql_log(ql_log_info, vha, 0x708b, "SRB not found to abort.\n");
	bsg_job->req->errors = bsg_job->reply->result = -ENXIO;
	return 0;

done:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	if (bsg_job->request->msgcode == FC_BSG_HST_CT)
		kfree(sp->fcport);
	qla2x00_rel_sp(vha, sp);
	return 0;
}