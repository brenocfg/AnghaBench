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
typedef  int uint32_t ;
struct lpfc_queue {size_t hba_index; int entry_count; int host_index; TYPE_1__* qe; } ;
struct lpfc_cqe {int dummy; } ;
struct TYPE_2__ {struct lpfc_cqe* cqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  bf_get_le32 (int /*<<< orphan*/ ,struct lpfc_cqe*) ; 
 int /*<<< orphan*/  lpfc_cqe_valid ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct lpfc_cqe *
lpfc_sli4_cq_get(struct lpfc_queue *q)
{
	struct lpfc_cqe *cqe;
	uint32_t idx;

	/* sanity check on queue memory */
	if (unlikely(!q))
		return NULL;

	/* If the next CQE is not valid then we are done */
	if (!bf_get_le32(lpfc_cqe_valid, q->qe[q->hba_index].cqe))
		return NULL;
	/* If the host has not yet processed the next entry then we are done */
	idx = ((q->hba_index + 1) % q->entry_count);
	if (idx == q->host_index)
		return NULL;

	cqe = q->qe[q->hba_index].cqe;
	q->hba_index = idx;
	return cqe;
}