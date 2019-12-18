#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct ehca_shca {int /*<<< orphan*/  ib_device; } ;
struct ehca_eqe {int /*<<< orphan*/  entry; } ;
struct ehca_cq {int /*<<< orphan*/  wait_completion; int /*<<< orphan*/  nr_events; } ;

/* Variables and functions */
 scalar_t__ EHCA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EQE_COMPLETION_EVENT ; 
 int /*<<< orphan*/  EQE_CQ_TOKEN ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comp_event_callback (struct ehca_cq*) ; 
 int /*<<< orphan*/  ehca_cq_idr ; 
 int /*<<< orphan*/  ehca_cq_idr_lock ; 
 int /*<<< orphan*/  ehca_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ ehca_scaling_code ; 
 struct ehca_cq* idr_find (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  parse_identifier (struct ehca_shca*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_comp_task (struct ehca_cq*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_eq_pending (struct ehca_cq*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void process_eqe(struct ehca_shca *shca, struct ehca_eqe *eqe)
{
	u64 eqe_value;
	u32 token;
	struct ehca_cq *cq;

	eqe_value = eqe->entry;
	ehca_dbg(&shca->ib_device, "eqe_value=%llx", eqe_value);
	if (EHCA_BMASK_GET(EQE_COMPLETION_EVENT, eqe_value)) {
		ehca_dbg(&shca->ib_device, "Got completion event");
		token = EHCA_BMASK_GET(EQE_CQ_TOKEN, eqe_value);
		read_lock(&ehca_cq_idr_lock);
		cq = idr_find(&ehca_cq_idr, token);
		if (cq)
			atomic_inc(&cq->nr_events);
		read_unlock(&ehca_cq_idr_lock);
		if (cq == NULL) {
			ehca_err(&shca->ib_device,
				 "Invalid eqe for non-existing cq token=%x",
				 token);
			return;
		}
		reset_eq_pending(cq);
		if (ehca_scaling_code)
			queue_comp_task(cq);
		else {
			comp_event_callback(cq);
			if (atomic_dec_and_test(&cq->nr_events))
				wake_up(&cq->wait_completion);
		}
	} else {
		ehca_dbg(&shca->ib_device, "Got non completion event");
		parse_identifier(shca, eqe_value);
	}
}