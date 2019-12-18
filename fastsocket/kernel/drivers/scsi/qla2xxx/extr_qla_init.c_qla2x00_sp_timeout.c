#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct srb_iocb {int /*<<< orphan*/  (* timeout ) (TYPE_2__*) ;} ;
struct req_que {int /*<<< orphan*/ ** outstanding_cmds; } ;
struct qla_hw_data {int /*<<< orphan*/  hardware_lock; struct req_que** req_q_map; } ;
struct TYPE_7__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_8__ {size_t handle; int /*<<< orphan*/  (* free ) (TYPE_4__*,TYPE_2__*) ;TYPE_1__ u; TYPE_3__* fcport; } ;
typedef  TYPE_2__ srb_t ;
struct TYPE_9__ {TYPE_4__* vha; } ;
typedef  TYPE_3__ fc_port_t ;
struct TYPE_10__ {struct qla_hw_data* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,TYPE_2__*) ; 

void
qla2x00_sp_timeout(unsigned long __data)
{
	srb_t *sp = (srb_t *)__data;
	struct srb_iocb *iocb;
	fc_port_t *fcport = sp->fcport;
	struct qla_hw_data *ha = fcport->vha->hw;
	struct req_que *req;
	unsigned long flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	req = ha->req_q_map[0];
	req->outstanding_cmds[sp->handle] = NULL;
	iocb = &sp->u.iocb_cmd;
	iocb->timeout(sp);
	sp->free(fcport->vha, sp);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);
}