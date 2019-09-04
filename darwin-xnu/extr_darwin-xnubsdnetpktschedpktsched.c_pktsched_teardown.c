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
struct ifclassq {int ifcq_type; int /*<<< orphan*/  ifcq_flags; int /*<<< orphan*/  ifcq_ifp; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IFCQF_ENABLED ; 
 int /*<<< orphan*/  IFCQ_IS_EMPTY (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
#define  PKTSCHEDT_FQ_CODEL 131 
#define  PKTSCHEDT_NONE 130 
#define  PKTSCHEDT_QFQ 129 
#define  PKTSCHEDT_TCQ 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int fq_if_teardown_ifclassq (struct ifclassq*) ; 
 int /*<<< orphan*/  if_qflush (int /*<<< orphan*/ ,int) ; 
 int qfq_teardown_ifclassq (struct ifclassq*) ; 
 int tcq_teardown_ifclassq (struct ifclassq*) ; 

int
pktsched_teardown(struct ifclassq *ifq)
{
	int error = 0;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	if_qflush(ifq->ifcq_ifp, 1);
	VERIFY(IFCQ_IS_EMPTY(ifq));

	ifq->ifcq_flags &= ~IFCQF_ENABLED;

	switch (ifq->ifcq_type) {
	case PKTSCHEDT_NONE:
		break;

	case PKTSCHEDT_TCQ:
		error = tcq_teardown_ifclassq(ifq);
		break;

	case PKTSCHEDT_QFQ:
		error = qfq_teardown_ifclassq(ifq);
		break;

	case PKTSCHEDT_FQ_CODEL:
		error = fq_if_teardown_ifclassq(ifq);
		break;
	default:
		error = ENXIO;
		break;
	}
	return (error);
}