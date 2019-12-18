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
typedef  int uint32_t ;
struct lpfc_register {scalar_t__ word0; } ;
struct lpfc_queue {size_t hba_index; size_t host_index; int entry_count; int queue_id; TYPE_3__* phba; TYPE_1__* qe; } ;
struct lpfc_cqe {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  EQCQDBregaddr; } ;
struct TYPE_6__ {TYPE_2__ sli4_hba; } ;
struct TYPE_4__ {struct lpfc_cqe* cqe; } ;

/* Variables and functions */
 int LPFC_CQID_HI_FIELD_SHIFT ; 
 int LPFC_QUEUE_TYPE_COMPLETION ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_register*,int) ; 
 int /*<<< orphan*/  bf_set_le32 (int /*<<< orphan*/ ,struct lpfc_cqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cqe_valid ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_arm ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_cqid_hi ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_cqid_lo ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_num_released ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_qt ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

uint32_t
lpfc_sli4_cq_release(struct lpfc_queue *q, bool arm)
{
	uint32_t released = 0;
	struct lpfc_cqe *temp_qe;
	struct lpfc_register doorbell;

	/* sanity check on queue memory */
	if (unlikely(!q))
		return 0;
	/* while there are valid entries */
	while (q->hba_index != q->host_index) {
		temp_qe = q->qe[q->host_index].cqe;
		bf_set_le32(lpfc_cqe_valid, temp_qe, 0);
		released++;
		q->host_index = ((q->host_index + 1) % q->entry_count);
	}
	if (unlikely(released == 0 && !arm))
		return 0;

	/* ring doorbell for number popped */
	doorbell.word0 = 0;
	if (arm)
		bf_set(lpfc_eqcq_doorbell_arm, &doorbell, 1);
	bf_set(lpfc_eqcq_doorbell_num_released, &doorbell, released);
	bf_set(lpfc_eqcq_doorbell_qt, &doorbell, LPFC_QUEUE_TYPE_COMPLETION);
	bf_set(lpfc_eqcq_doorbell_cqid_hi, &doorbell,
			(q->queue_id >> LPFC_CQID_HI_FIELD_SHIFT));
	bf_set(lpfc_eqcq_doorbell_cqid_lo, &doorbell, q->queue_id);
	writel(doorbell.word0, q->phba->sli4_hba.EQCQDBregaddr);
	return released;
}