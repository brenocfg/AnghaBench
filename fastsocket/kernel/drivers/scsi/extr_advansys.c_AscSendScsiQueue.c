#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uchar ;
struct TYPE_16__ {int /*<<< orphan*/ * cur_dvc_qng; int /*<<< orphan*/  cur_total_qng; scalar_t__ last_q_shortage; int /*<<< orphan*/  iop_base; } ;
struct TYPE_14__ {int q_no; } ;
struct TYPE_12__ {int target_ix; } ;
struct TYPE_15__ {TYPE_3__ q1; TYPE_2__* sg_head; TYPE_1__ q2; } ;
struct TYPE_13__ {int queue_cnt; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_4__ ASC_SCSI_Q ;
typedef  TYPE_5__ ASC_DVC_VAR ;

/* Variables and functions */
 int ASC_QLINK_END ; 
 int ASC_TIX_TO_TID (int) ; 
 int AscAllocFreeQueue (int /*<<< orphan*/ ,int) ; 
 int AscAllocMultipleFreeQueue (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ AscGetVarFreeQHead (int /*<<< orphan*/ ) ; 
 int AscPutReadyQueue (TYPE_5__*,TYPE_4__*,int) ; 
 int AscPutReadySgListQueue (TYPE_5__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  AscPutVarFreeQHead (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
AscSendScsiQueue(ASC_DVC_VAR *asc_dvc, ASC_SCSI_Q *scsiq, uchar n_q_required)
{
	PortAddr iop_base;
	uchar free_q_head;
	uchar next_qp;
	uchar tid_no;
	uchar target_ix;
	int sta;

	iop_base = asc_dvc->iop_base;
	target_ix = scsiq->q2.target_ix;
	tid_no = ASC_TIX_TO_TID(target_ix);
	sta = 0;
	free_q_head = (uchar)AscGetVarFreeQHead(iop_base);
	if (n_q_required > 1) {
		next_qp = AscAllocMultipleFreeQueue(iop_base, free_q_head,
						    (uchar)n_q_required);
		if (next_qp != ASC_QLINK_END) {
			asc_dvc->last_q_shortage = 0;
			scsiq->sg_head->queue_cnt = n_q_required - 1;
			scsiq->q1.q_no = free_q_head;
			sta = AscPutReadySgListQueue(asc_dvc, scsiq,
						     free_q_head);
		}
	} else if (n_q_required == 1) {
		next_qp = AscAllocFreeQueue(iop_base, free_q_head);
		if (next_qp != ASC_QLINK_END) {
			scsiq->q1.q_no = free_q_head;
			sta = AscPutReadyQueue(asc_dvc, scsiq, free_q_head);
		}
	}
	if (sta == 1) {
		AscPutVarFreeQHead(iop_base, next_qp);
		asc_dvc->cur_total_qng += n_q_required;
		asc_dvc->cur_dvc_qng[tid_no]++;
	}
	return sta;
}