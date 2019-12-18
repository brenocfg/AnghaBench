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
struct qfq_if {int dummy; } ;
struct ifclassq {scalar_t__ ifcq_type; TYPE_1__* ifcq_disc_slots; struct qfq_if* ifcq_disc; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cl; scalar_t__ qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int IFCQ_SC_MAX ; 
 scalar_t__ PKTSCHEDT_QFQ ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ifclassq_detach (struct ifclassq*) ; 
 int /*<<< orphan*/  qfq_destroy_locked (struct qfq_if*) ; 

int
qfq_teardown_ifclassq(struct ifclassq *ifq)
{
	struct qfq_if *qif = ifq->ifcq_disc;
	int i;

	IFCQ_LOCK_ASSERT_HELD(ifq);
	VERIFY(qif != NULL && ifq->ifcq_type == PKTSCHEDT_QFQ);

	(void) qfq_destroy_locked(qif);

	ifq->ifcq_disc = NULL;
	for (i = 0; i < IFCQ_SC_MAX; i++) {
		ifq->ifcq_disc_slots[i].qid = 0;
		ifq->ifcq_disc_slots[i].cl = NULL;
	}

	return (ifclassq_detach(ifq));
}