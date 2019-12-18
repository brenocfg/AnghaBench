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
struct TYPE_4__ {int /*<<< orphan*/  used; } ;
struct be_queue_info {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ q; struct be_queue_info cq; } ;
struct TYPE_6__ {TYPE_2__ mcc_obj; } ;
struct beiscsi_hba {TYPE_3__ ctrl; } ;
struct be_mcc_compl {int flags; } ;
struct be_async_event_link_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_MBOX ; 
 int CQE_FLAGS_ASYNC_MASK ; 
 int CQE_FLAGS_COMPLETED_MASK ; 
 int CQE_FLAGS_VALID_MASK ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_mcc_compl_process_isr (TYPE_3__*,struct be_mcc_compl*) ; 
 int /*<<< orphan*/  beiscsi_async_link_state_process (struct beiscsi_hba*,struct be_async_event_link_state*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hwi_ring_cq_db (struct beiscsi_hba*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_link_state_evt (int) ; 
 void* le32_to_cpu (int) ; 
 int /*<<< orphan*/  queue_tail_inc (struct be_queue_info*) ; 
 struct be_mcc_compl* queue_tail_node (struct be_queue_info*) ; 

__attribute__((used)) static void  beiscsi_process_mcc_isr(struct beiscsi_hba *phba)
{
	struct be_queue_info *mcc_cq;
	struct  be_mcc_compl *mcc_compl;
	unsigned int num_processed = 0;

	mcc_cq = &phba->ctrl.mcc_obj.cq;
	mcc_compl = queue_tail_node(mcc_cq);
	mcc_compl->flags = le32_to_cpu(mcc_compl->flags);
	while (mcc_compl->flags & CQE_FLAGS_VALID_MASK) {

		if (num_processed >= 32) {
			hwi_ring_cq_db(phba, mcc_cq->id,
					num_processed, 0, 0);
			num_processed = 0;
		}
		if (mcc_compl->flags & CQE_FLAGS_ASYNC_MASK) {
			/* Interpret flags as an async trailer */
			if (is_link_state_evt(mcc_compl->flags))
				/* Interpret compl as a async link evt */
				beiscsi_async_link_state_process(phba,
				(struct be_async_event_link_state *) mcc_compl);
			else
				beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_MBOX,
					    "BM_%d :  Unsupported Async Event, flags"
					    " = 0x%08x\n",
					    mcc_compl->flags);
		} else if (mcc_compl->flags & CQE_FLAGS_COMPLETED_MASK) {
			be_mcc_compl_process_isr(&phba->ctrl, mcc_compl);
			atomic_dec(&phba->ctrl.mcc_obj.q.used);
		}

		mcc_compl->flags = 0;
		queue_tail_inc(mcc_cq);
		mcc_compl = queue_tail_node(mcc_cq);
		mcc_compl->flags = le32_to_cpu(mcc_compl->flags);
		num_processed++;
	}

	if (num_processed > 0)
		hwi_ring_cq_db(phba, mcc_cq->id, num_processed, 1, 0);

}