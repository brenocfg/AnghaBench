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
struct TYPE_5__ {int tsk_mgmt_func; int /*<<< orphan*/  lun; int /*<<< orphan*/  task_tag; } ;
struct TYPE_6__ {TYPE_2__ tsk_mgmt; } ;
union viosrp_iu {TYPE_3__ srp; } ;
struct scsi_lun {int dummy; } ;
struct iu_entry {TYPE_1__* target; } ;
struct TYPE_4__ {scalar_t__ shost; } ;

/* Variables and functions */
 int ABORT_TASK ; 
 int ABORT_TASK_SET ; 
 int CLEAR_ACA ; 
 int CLEAR_TASK_SET ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int LOGICAL_UNIT_RESET ; 
#define  SRP_TSK_ABORT_TASK 132 
#define  SRP_TSK_ABORT_TASK_SET 131 
#define  SRP_TSK_CLEAR_ACA 130 
#define  SRP_TSK_CLEAR_TASK_SET 129 
#define  SRP_TSK_LUN_RESET 128 
 int /*<<< orphan*/  dprintk (char*,struct iu_entry*,int) ; 
 int /*<<< orphan*/  scsi_tgt_tsk_mgmt_request (scalar_t__,unsigned long,int,int /*<<< orphan*/ ,struct scsi_lun*,struct iu_entry*) ; 
 int /*<<< orphan*/  send_rsp (struct iu_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 union viosrp_iu* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static int process_tsk_mgmt(struct iu_entry *iue)
{
	union viosrp_iu *iu = vio_iu(iue);
	int fn;

	dprintk("%p %u\n", iue, iu->srp.tsk_mgmt.tsk_mgmt_func);

	switch (iu->srp.tsk_mgmt.tsk_mgmt_func) {
	case SRP_TSK_ABORT_TASK:
		fn = ABORT_TASK;
		break;
	case SRP_TSK_ABORT_TASK_SET:
		fn = ABORT_TASK_SET;
		break;
	case SRP_TSK_CLEAR_TASK_SET:
		fn = CLEAR_TASK_SET;
		break;
	case SRP_TSK_LUN_RESET:
		fn = LOGICAL_UNIT_RESET;
		break;
	case SRP_TSK_CLEAR_ACA:
		fn = CLEAR_ACA;
		break;
	default:
		fn = 0;
	}
	if (fn)
		scsi_tgt_tsk_mgmt_request(iue->target->shost,
					  (unsigned long)iue->target->shost,
					  fn,
					  iu->srp.tsk_mgmt.task_tag,
					  (struct scsi_lun *) &iu->srp.tsk_mgmt.lun,
					  iue);
	else
		send_rsp(iue, NULL, ILLEGAL_REQUEST, 0x20);

	return !fn;
}