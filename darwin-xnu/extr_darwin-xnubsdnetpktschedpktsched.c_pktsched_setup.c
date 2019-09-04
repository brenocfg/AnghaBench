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
typedef  int u_int32_t ;
struct ifclassq {int ifcq_type; int ifcq_flags; int /*<<< orphan*/ * ifcq_request; int /*<<< orphan*/ * ifcq_dequeue_sc; int /*<<< orphan*/ * ifcq_dequeue; int /*<<< orphan*/ * ifcq_enqueue; int /*<<< orphan*/ * ifcq_disc; } ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;

/* Variables and functions */
 int ENXIO ; 
 int IFCQF_ENABLED ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
#define  PKTSCHEDT_FQ_CODEL 130 
 scalar_t__ PKTSCHEDT_NONE ; 
#define  PKTSCHEDT_QFQ 129 
#define  PKTSCHEDT_TCQ 128 
 int /*<<< orphan*/  VERIFY (int) ; 
 int fq_if_setup_ifclassq (struct ifclassq*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ machclk_freq ; 
 int /*<<< orphan*/  pktsched_teardown (struct ifclassq*) ; 
 int qfq_setup_ifclassq (struct ifclassq*,int,int /*<<< orphan*/ ) ; 
 int tcq_setup_ifclassq (struct ifclassq*,int,int /*<<< orphan*/ ) ; 

int
pktsched_setup(struct ifclassq *ifq, u_int32_t scheduler, u_int32_t sflags,
    classq_pkt_type_t ptype)
{
	int error = 0;
	u_int32_t rflags;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	VERIFY(machclk_freq != 0);

	/* Nothing to do unless the scheduler type changes */
	if (ifq->ifcq_type == scheduler)
		return (0);

	/*
	 * Remember the flags that need to be restored upon success, as
	 * they may be cleared when we tear down existing scheduler.
	 */
	rflags = (ifq->ifcq_flags & IFCQF_ENABLED);

	if (ifq->ifcq_type != PKTSCHEDT_NONE) {
		(void) pktsched_teardown(ifq);

		/* Teardown should have succeeded */
		VERIFY(ifq->ifcq_type == PKTSCHEDT_NONE);
		VERIFY(ifq->ifcq_disc == NULL);
		VERIFY(ifq->ifcq_enqueue == NULL);
		VERIFY(ifq->ifcq_dequeue == NULL);
		VERIFY(ifq->ifcq_dequeue_sc == NULL);
		VERIFY(ifq->ifcq_request == NULL);
	}

	switch (scheduler) {
	case PKTSCHEDT_TCQ:
		error = tcq_setup_ifclassq(ifq, sflags, ptype);
		break;

	case PKTSCHEDT_QFQ:
		error = qfq_setup_ifclassq(ifq, sflags, ptype);
		break;
	case PKTSCHEDT_FQ_CODEL:
		error = fq_if_setup_ifclassq(ifq, sflags, ptype);
		break;
	default:
		error = ENXIO;
		break;
	}

	if (error == 0)
		ifq->ifcq_flags |= rflags;

	return (error);
}