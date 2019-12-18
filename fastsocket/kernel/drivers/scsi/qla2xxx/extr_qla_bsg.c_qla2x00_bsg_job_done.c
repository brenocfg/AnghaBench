#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {int dummy; } ;
struct fc_bsg_job {int /*<<< orphan*/  (* job_done ) (struct fc_bsg_job*) ;TYPE_2__* reply; } ;
struct TYPE_5__ {struct fc_bsg_job* bsg_job; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* free ) (struct scsi_qla_host*,TYPE_3__*) ;TYPE_1__ u; } ;
typedef  TYPE_3__ srb_t ;
typedef  struct scsi_qla_host scsi_qla_host_t ;
struct TYPE_6__ {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fc_bsg_job*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_qla_host*,TYPE_3__*) ; 

void
qla2x00_bsg_job_done(void *data, void *ptr, int res)
{
	srb_t *sp = (srb_t*)ptr;
	struct scsi_qla_host *vha = (scsi_qla_host_t *)data;
	struct fc_bsg_job *bsg_job = sp->u.bsg_job;

	bsg_job->reply->result = res;
	bsg_job->job_done(bsg_job);
	sp->free(vha, sp);
}