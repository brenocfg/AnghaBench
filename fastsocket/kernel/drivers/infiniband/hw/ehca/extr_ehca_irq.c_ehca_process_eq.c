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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ehca_eq {int /*<<< orphan*/  irq_spinlock; struct ehca_eqe_cache_entry* eqe_cache; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  ipz_queue; int /*<<< orphan*/  ist; } ;
struct ehca_shca {struct ehca_eq eq; int /*<<< orphan*/  ib_device; int /*<<< orphan*/  ipz_hca_handle; } ;
struct ehca_eqe_cache_entry {TYPE_1__* eqe; struct ehca_cq* cq; } ;
struct ehca_eqe {int dummy; } ;
struct ehca_cq {int /*<<< orphan*/  wait_completion; int /*<<< orphan*/  nr_events; } ;
struct TYPE_2__ {scalar_t__ entry; } ;

/* Variables and functions */
 scalar_t__ EHCA_BMASK_GET (int /*<<< orphan*/ ,scalar_t__) ; 
 int EHCA_EQE_CACHE_SIZE ; 
 int /*<<< orphan*/  EQE_COMPLETION_EVENT ; 
 int /*<<< orphan*/  EQE_CQ_TOKEN ; 
 scalar_t__ H_SUCCESS ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comp_event_callback (struct ehca_cq*) ; 
 int /*<<< orphan*/  ehca_cq_idr ; 
 int /*<<< orphan*/  ehca_cq_idr_lock ; 
 int /*<<< orphan*/  ehca_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 void* ehca_poll_eq (struct ehca_shca*,struct ehca_eq*) ; 
 scalar_t__ ehca_scaling_code ; 
 scalar_t__ hipz_h_eoi (int /*<<< orphan*/ ) ; 
 int hipz_h_query_int_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ehca_cq* idr_find (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  iosync () ; 
 int /*<<< orphan*/  ipz_eqit_eq_peek_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_identifier (struct ehca_shca*,scalar_t__) ; 
 int /*<<< orphan*/  process_eqe (struct ehca_shca*,struct ehca_eqe*) ; 
 int /*<<< orphan*/  queue_comp_task (struct ehca_cq*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_eq_pending (struct ehca_cq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ehca_process_eq(struct ehca_shca *shca, int is_irq)
{
	struct ehca_eq *eq = &shca->eq;
	struct ehca_eqe_cache_entry *eqe_cache = eq->eqe_cache;
	u64 eqe_value, ret;
	int eqe_cnt, i;
	int eq_empty = 0;

	spin_lock(&eq->irq_spinlock);
	if (is_irq) {
		const int max_query_cnt = 100;
		int query_cnt = 0;
		int int_state = 1;
		do {
			int_state = hipz_h_query_int_state(
				shca->ipz_hca_handle, eq->ist);
			query_cnt++;
			iosync();
		} while (int_state && query_cnt < max_query_cnt);
		if (unlikely((query_cnt == max_query_cnt)))
			ehca_dbg(&shca->ib_device, "int_state=%x query_cnt=%x",
				 int_state, query_cnt);
	}

	/* read out all eqes */
	eqe_cnt = 0;
	do {
		u32 token;
		eqe_cache[eqe_cnt].eqe = ehca_poll_eq(shca, eq);
		if (!eqe_cache[eqe_cnt].eqe)
			break;
		eqe_value = eqe_cache[eqe_cnt].eqe->entry;
		if (EHCA_BMASK_GET(EQE_COMPLETION_EVENT, eqe_value)) {
			token = EHCA_BMASK_GET(EQE_CQ_TOKEN, eqe_value);
			read_lock(&ehca_cq_idr_lock);
			eqe_cache[eqe_cnt].cq = idr_find(&ehca_cq_idr, token);
			if (eqe_cache[eqe_cnt].cq)
				atomic_inc(&eqe_cache[eqe_cnt].cq->nr_events);
			read_unlock(&ehca_cq_idr_lock);
			if (!eqe_cache[eqe_cnt].cq) {
				ehca_err(&shca->ib_device,
					 "Invalid eqe for non-existing cq "
					 "token=%x", token);
				continue;
			}
		} else
			eqe_cache[eqe_cnt].cq = NULL;
		eqe_cnt++;
	} while (eqe_cnt < EHCA_EQE_CACHE_SIZE);
	if (!eqe_cnt) {
		if (is_irq)
			ehca_dbg(&shca->ib_device,
				 "No eqe found for irq event");
		goto unlock_irq_spinlock;
	} else if (!is_irq) {
		ret = hipz_h_eoi(eq->ist);
		if (ret != H_SUCCESS)
			ehca_err(&shca->ib_device,
				 "bad return code EOI -rc = %lld\n", ret);
		ehca_dbg(&shca->ib_device, "deadman found %x eqe", eqe_cnt);
	}
	if (unlikely(eqe_cnt == EHCA_EQE_CACHE_SIZE))
		ehca_dbg(&shca->ib_device, "too many eqes for one irq event");
	/* enable irq for new packets */
	for (i = 0; i < eqe_cnt; i++) {
		if (eq->eqe_cache[i].cq)
			reset_eq_pending(eq->eqe_cache[i].cq);
	}
	/* check eq */
	spin_lock(&eq->spinlock);
	eq_empty = (!ipz_eqit_eq_peek_valid(&shca->eq.ipz_queue));
	spin_unlock(&eq->spinlock);
	/* call completion handler for cached eqes */
	for (i = 0; i < eqe_cnt; i++)
		if (eq->eqe_cache[i].cq) {
			if (ehca_scaling_code)
				queue_comp_task(eq->eqe_cache[i].cq);
			else {
				struct ehca_cq *cq = eq->eqe_cache[i].cq;
				comp_event_callback(cq);
				if (atomic_dec_and_test(&cq->nr_events))
					wake_up(&cq->wait_completion);
			}
		} else {
			ehca_dbg(&shca->ib_device, "Got non completion event");
			parse_identifier(shca, eq->eqe_cache[i].eqe->entry);
		}
	/* poll eq if not empty */
	if (eq_empty)
		goto unlock_irq_spinlock;
	do {
		struct ehca_eqe *eqe;
		eqe = ehca_poll_eq(shca, &shca->eq);
		if (!eqe)
			break;
		process_eqe(shca, eqe);
	} while (1);

unlock_irq_spinlock:
	spin_unlock(&eq->irq_spinlock);
}