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
struct ifclassq {int /*<<< orphan*/ * ifcq_request; int /*<<< orphan*/ * ifcq_dequeue_sc; int /*<<< orphan*/ * ifcq_dequeue; int /*<<< orphan*/ * ifcq_enqueue; int /*<<< orphan*/ * ifcq_disc; int /*<<< orphan*/  ifcq_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int /*<<< orphan*/  PKTSCHEDT_NONE ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 

int
ifclassq_detach(struct ifclassq *ifq)
{
	IFCQ_LOCK_ASSERT_HELD(ifq);

	VERIFY(ifq->ifcq_disc == NULL);

	ifq->ifcq_type = PKTSCHEDT_NONE;
	ifq->ifcq_disc = NULL;
	ifq->ifcq_enqueue = NULL;
	ifq->ifcq_dequeue = NULL;
	ifq->ifcq_dequeue_sc = NULL;
	ifq->ifcq_request = NULL;

	return (0);
}