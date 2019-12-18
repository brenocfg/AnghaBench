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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ehca_shca {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
struct ehca_cq {int /*<<< orphan*/  wait_completion; int /*<<< orphan*/  nr_events; TYPE_1__ ipz_cq_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EQE_CQ_TOKEN ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehca_cq_idr ; 
 int /*<<< orphan*/  ehca_cq_idr_lock ; 
 int /*<<< orphan*/  ehca_error_data (struct ehca_shca*,struct ehca_cq*,int /*<<< orphan*/ ) ; 
 struct ehca_cq* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cq_event_callback(struct ehca_shca *shca,
			      u64 eqe)
{
	struct ehca_cq *cq;
	u32 token = EHCA_BMASK_GET(EQE_CQ_TOKEN, eqe);

	read_lock(&ehca_cq_idr_lock);
	cq = idr_find(&ehca_cq_idr, token);
	if (cq)
		atomic_inc(&cq->nr_events);
	read_unlock(&ehca_cq_idr_lock);

	if (!cq)
		return;

	ehca_error_data(shca, cq, cq->ipz_cq_handle.handle);

	if (atomic_dec_and_test(&cq->nr_events))
		wake_up(&cq->wait_completion);

	return;
}