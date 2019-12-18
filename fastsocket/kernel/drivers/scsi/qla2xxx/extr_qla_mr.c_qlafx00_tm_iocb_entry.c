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
typedef  scalar_t__ uint16_t ;
struct tsk_mgmt_entry_fx00 {int dummy; } ;
struct TYPE_8__ {scalar_t__ comp_status; } ;
struct TYPE_9__ {TYPE_2__ tmf; } ;
struct srb_iocb {TYPE_3__ u; } ;
struct req_que {int dummy; } ;
struct TYPE_7__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* done ) (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ;TYPE_1__ u; } ;
typedef  TYPE_4__ srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ CS_COMPLETE ; 
 scalar_t__ CS_INCOMPLETE ; 
 scalar_t__ SS_RESPONSE_INFO_LEN_VALID ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qlafx00_tm_iocb_entry(scsi_qla_host_t *vha, struct req_que *req,
		      struct tsk_mgmt_entry_fx00 *pkt, srb_t *sp,
		      uint16_t sstatus, uint16_t cpstatus)
{
	struct srb_iocb *tmf;

	tmf = &sp->u.iocb_cmd;
	if (cpstatus != CS_COMPLETE ||
	    (sstatus & SS_RESPONSE_INFO_LEN_VALID))
		cpstatus = CS_INCOMPLETE;
	tmf->u.tmf.comp_status = cpstatus;
	sp->done(vha, sp, 0);
}