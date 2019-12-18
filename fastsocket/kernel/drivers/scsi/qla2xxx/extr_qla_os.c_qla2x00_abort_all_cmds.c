#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct req_que {int num_outstanding_cmds; TYPE_1__** outstanding_cmds; } ;
struct qla_hw_data {int max_req_queues; int /*<<< orphan*/  hardware_lock; struct req_que** req_q_map; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* done ) (TYPE_2__*,TYPE_1__*,int) ;} ;
typedef  TYPE_1__ srb_t ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*,int) ; 

void
qla2x00_abort_all_cmds(scsi_qla_host_t *vha, int res)
{
	int que, cnt;
	unsigned long flags;
	srb_t *sp;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	for (que = 0; que < ha->max_req_queues; que++) {
		req = ha->req_q_map[que];
		if (!req)
			continue;
		if (!req->outstanding_cmds)
			continue;
		for (cnt = 1; cnt < req->num_outstanding_cmds; cnt++) {
			sp = req->outstanding_cmds[cnt];
			if (sp) {
				req->outstanding_cmds[cnt] = NULL;
				sp->done(vha, sp, res);
			}
		}
	}
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
}