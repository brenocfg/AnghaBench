#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct be_queue_info {scalar_t__ created; } ;
struct TYPE_2__ {struct be_queue_info cq; struct be_queue_info q; } ;
struct be_ctrl_info {TYPE_1__ mcc_obj; } ;
struct beiscsi_hba {struct be_ctrl_info ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  QTYPE_CQ ; 
 int /*<<< orphan*/  QTYPE_MCCQ ; 
 int /*<<< orphan*/  be_queue_free (struct beiscsi_hba*,struct be_queue_info*) ; 
 int /*<<< orphan*/  beiscsi_cmd_q_destroy (struct be_ctrl_info*,struct be_queue_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_mcc_queues_destroy(struct beiscsi_hba *phba)
{
	struct be_queue_info *q;
	struct be_ctrl_info *ctrl = &phba->ctrl;

	q = &phba->ctrl.mcc_obj.q;
	if (q->created)
		beiscsi_cmd_q_destroy(ctrl, q, QTYPE_MCCQ);
	be_queue_free(phba, q);

	q = &phba->ctrl.mcc_obj.cq;
	if (q->created)
		beiscsi_cmd_q_destroy(ctrl, q, QTYPE_CQ);
	be_queue_free(phba, q);
}