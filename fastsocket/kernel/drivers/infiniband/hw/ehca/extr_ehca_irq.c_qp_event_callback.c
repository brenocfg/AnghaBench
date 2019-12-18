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
struct ehca_qp {scalar_t__ ext_type; int /*<<< orphan*/  wait_completion; int /*<<< orphan*/  nr_events; TYPE_1__ ipz_qp_handle; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  EHCA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EQE_QP_TOKEN ; 
 scalar_t__ EQPT_SRQ ; 
 scalar_t__ EQPT_SRQBASE ; 
 int IB_EVENT_QP_LAST_WQE_REACHED ; 
 int IB_EVENT_SRQ_ERR ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispatch_qp_event (struct ehca_shca*,struct ehca_qp*,int) ; 
 int /*<<< orphan*/  ehca_error_data (struct ehca_shca*,struct ehca_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehca_qp_idr ; 
 int /*<<< orphan*/  ehca_qp_idr_lock ; 
 struct ehca_qp* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qp_event_callback(struct ehca_shca *shca, u64 eqe,
			      enum ib_event_type event_type, int fatal)
{
	struct ehca_qp *qp;
	u32 token = EHCA_BMASK_GET(EQE_QP_TOKEN, eqe);

	read_lock(&ehca_qp_idr_lock);
	qp = idr_find(&ehca_qp_idr, token);
	if (qp)
		atomic_inc(&qp->nr_events);
	read_unlock(&ehca_qp_idr_lock);

	if (!qp)
		return;

	if (fatal)
		ehca_error_data(shca, qp, qp->ipz_qp_handle.handle);

	dispatch_qp_event(shca, qp, fatal && qp->ext_type == EQPT_SRQ ?
			  IB_EVENT_SRQ_ERR : event_type);

	/*
	 * eHCA only processes one WQE at a time for SRQ base QPs,
	 * so the last WQE has been processed as soon as the QP enters
	 * error state.
	 */
	if (fatal && qp->ext_type == EQPT_SRQBASE)
		dispatch_qp_event(shca, qp, IB_EVENT_QP_LAST_WQE_REACHED);

	if (atomic_dec_and_test(&qp->nr_events))
		wake_up(&qp->wait_completion);
	return;
}