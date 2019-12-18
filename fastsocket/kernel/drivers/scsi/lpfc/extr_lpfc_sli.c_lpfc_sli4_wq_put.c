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
struct lpfc_register {scalar_t__ word0; } ;
struct TYPE_6__ {struct lpfc_register wqe_com; } ;
union lpfc_wqe {TYPE_3__ generic; } ;
typedef  int uint32_t ;
struct lpfc_queue {size_t host_index; int entry_count; int hba_index; int entry_repost; int queue_id; scalar_t__ db_format; int /*<<< orphan*/  db_regaddr; int /*<<< orphan*/  entry_size; TYPE_2__* phba; int /*<<< orphan*/  WQ_posted; int /*<<< orphan*/  WQ_overflow; TYPE_1__* qe; } ;
struct TYPE_5__ {int sli3_options; } ;
struct TYPE_4__ {union lpfc_wqe* wqe; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ LPFC_DB_LIST_FORMAT ; 
 scalar_t__ LPFC_DB_RING_FORMAT ; 
 int LPFC_SLI4_PHWQ_ENABLED ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_register*,int) ; 
 int /*<<< orphan*/  lpfc_sli_pcimem_bcopy (union lpfc_wqe*,union lpfc_wqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_wq_db_list_fm_id ; 
 int /*<<< orphan*/  lpfc_wq_db_list_fm_index ; 
 int /*<<< orphan*/  lpfc_wq_db_list_fm_num_posted ; 
 int /*<<< orphan*/  lpfc_wq_db_ring_fm_id ; 
 int /*<<< orphan*/  lpfc_wq_db_ring_fm_num_posted ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wqe_wqec ; 
 int /*<<< orphan*/  wqe_wqid ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_sli4_wq_put(struct lpfc_queue *q, union lpfc_wqe *wqe)
{
	union lpfc_wqe *temp_wqe;
	struct lpfc_register doorbell;
	uint32_t host_index;
	uint32_t idx;

	/* sanity check on queue memory */
	if (unlikely(!q))
		return -ENOMEM;
	temp_wqe = q->qe[q->host_index].wqe;

	/* If the host has not yet processed the next entry then we are done */
	idx = ((q->host_index + 1) % q->entry_count);
	if (idx == q->hba_index) {
		q->WQ_overflow++;
		return -ENOMEM;
	}
	q->WQ_posted++;
	/* set consumption flag every once in a while */
	if (!((q->host_index + 1) % q->entry_repost))
		bf_set(wqe_wqec, &wqe->generic.wqe_com, 1);
	if (q->phba->sli3_options & LPFC_SLI4_PHWQ_ENABLED)
		bf_set(wqe_wqid, &wqe->generic.wqe_com, q->queue_id);
	lpfc_sli_pcimem_bcopy(wqe, temp_wqe, q->entry_size);

	/* Update the host index before invoking device */
	host_index = q->host_index;
	q->host_index = idx;

	/* Ring Doorbell */
	doorbell.word0 = 0;
	if (q->db_format == LPFC_DB_LIST_FORMAT) {
		bf_set(lpfc_wq_db_list_fm_num_posted, &doorbell, 1);
		bf_set(lpfc_wq_db_list_fm_index, &doorbell, host_index);
		bf_set(lpfc_wq_db_list_fm_id, &doorbell, q->queue_id);
	} else if (q->db_format == LPFC_DB_RING_FORMAT) {
		bf_set(lpfc_wq_db_ring_fm_num_posted, &doorbell, 1);
		bf_set(lpfc_wq_db_ring_fm_id, &doorbell, q->queue_id);
	} else {
		return -EINVAL;
	}
	writel(doorbell.word0, q->db_regaddr);

	return 0;
}