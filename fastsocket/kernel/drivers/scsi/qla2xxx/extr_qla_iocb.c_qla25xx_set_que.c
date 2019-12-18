#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_4__* request; } ;
struct rsp_que {int dummy; } ;
struct TYPE_8__ {scalar_t__ cpu_affinity_enabled; } ;
struct qla_hw_data {int max_rsp_queues; struct rsp_que** rsp_q_map; TYPE_1__ flags; } ;
struct TYPE_12__ {TYPE_3__* fcport; } ;
typedef  TYPE_5__ srb_t ;
struct TYPE_11__ {int cpu; } ;
struct TYPE_10__ {TYPE_2__* vha; } ;
struct TYPE_9__ {struct qla_hw_data* hw; } ;

/* Variables and functions */
 struct scsi_cmnd* GET_CMD_SP (TYPE_5__*) ; 

__attribute__((used)) static void qla25xx_set_que(srb_t *sp, struct rsp_que **rsp)
{
	struct scsi_cmnd *cmd = GET_CMD_SP(sp);
	struct qla_hw_data *ha = sp->fcport->vha->hw;
	int affinity = cmd->request->cpu;

	if (ha->flags.cpu_affinity_enabled && affinity >= 0 &&
		affinity < ha->max_rsp_queues - 1)
		*rsp = ha->rsp_q_map[affinity + 1];
	 else
		*rsp = ha->rsp_q_map[0];
}