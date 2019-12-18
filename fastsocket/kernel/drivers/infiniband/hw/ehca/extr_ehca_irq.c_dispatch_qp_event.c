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
struct TYPE_5__ {TYPE_3__* qp; TYPE_1__* srq; } ;
struct ib_event {int event; TYPE_2__ element; int /*<<< orphan*/ * device; } ;
struct ehca_shca {int /*<<< orphan*/  ib_device; } ;
struct TYPE_6__ {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  srq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;} ;
struct ehca_qp {scalar_t__ ext_type; TYPE_3__ ib_qp; TYPE_1__ ib_srq; int /*<<< orphan*/  mig_armed; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 scalar_t__ EQPT_SRQ ; 
 int IB_EVENT_PATH_MIG ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ib_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispatch_qp_event(struct ehca_shca *shca, struct ehca_qp *qp,
			      enum ib_event_type event_type)
{
	struct ib_event event;

	/* PATH_MIG without the QP ever having been armed is false alarm */
	if (event_type == IB_EVENT_PATH_MIG && !qp->mig_armed)
		return;

	event.device = &shca->ib_device;
	event.event = event_type;

	if (qp->ext_type == EQPT_SRQ) {
		if (!qp->ib_srq.event_handler)
			return;

		event.element.srq = &qp->ib_srq;
		qp->ib_srq.event_handler(&event, qp->ib_srq.srq_context);
	} else {
		if (!qp->ib_qp.event_handler)
			return;

		event.element.qp = &qp->ib_qp;
		qp->ib_qp.event_handler(&event, qp->ib_qp.qp_context);
	}
}