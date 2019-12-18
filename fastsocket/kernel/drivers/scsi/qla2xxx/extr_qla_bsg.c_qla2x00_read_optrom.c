#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ nic_core_reset_hdlr_active; } ;
struct qla_hw_data {int /*<<< orphan*/  optrom_state; int /*<<< orphan*/ * optrom_buffer; int /*<<< orphan*/  optrom_region_size; int /*<<< orphan*/  optrom_region_start; TYPE_2__* isp_ops; TYPE_1__ flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct fc_bsg_job {int /*<<< orphan*/  (* job_done ) (struct fc_bsg_job*) ;TYPE_4__* reply; TYPE_3__ reply_payload; struct Scsi_Host* shost; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_13__ {struct qla_hw_data* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;
struct TYPE_12__ {int /*<<< orphan*/  result; int /*<<< orphan*/  reply_payload_rcv_len; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* read_optrom ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DID_OK ; 
 int EBUSY ; 
 int /*<<< orphan*/  QLA_SWAITING ; 
 int qla2x00_optrom_setup (struct fc_bsg_job*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct fc_bsg_job*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla2x00_read_optrom(struct fc_bsg_job *bsg_job)
{
	struct Scsi_Host *host = bsg_job->shost;
	scsi_qla_host_t *vha = shost_priv(host);
	struct qla_hw_data *ha = vha->hw;
	int rval = 0;

	if (ha->flags.nic_core_reset_hdlr_active)
		return -EBUSY;

	rval = qla2x00_optrom_setup(bsg_job, vha, 0);
	if (rval)
		return rval;

	ha->isp_ops->read_optrom(vha, ha->optrom_buffer,
	    ha->optrom_region_start, ha->optrom_region_size);

	sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
	    bsg_job->reply_payload.sg_cnt, ha->optrom_buffer,
	    ha->optrom_region_size);

	bsg_job->reply->reply_payload_rcv_len = ha->optrom_region_size;
	bsg_job->reply->result = DID_OK;
	vfree(ha->optrom_buffer);
	ha->optrom_buffer = NULL;
	ha->optrom_state = QLA_SWAITING;
	bsg_job->job_done(bsg_job);
	return rval;
}