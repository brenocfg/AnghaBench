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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ifclassq {int ifcq_type; } ;
struct if_ifclassq_stats {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
#define  PKTSCHEDT_FQ_CODEL 130 
#define  PKTSCHEDT_QFQ 129 
#define  PKTSCHEDT_TCQ 128 
 int fq_if_getqstats_ifclassq (struct ifclassq*,int /*<<< orphan*/ ,struct if_ifclassq_stats*) ; 
 int qfq_getqstats_ifclassq (struct ifclassq*,int /*<<< orphan*/ ,struct if_ifclassq_stats*) ; 
 int tcq_getqstats_ifclassq (struct ifclassq*,int /*<<< orphan*/ ,struct if_ifclassq_stats*) ; 

int
pktsched_getqstats(struct ifclassq *ifq, u_int32_t qid,
    struct if_ifclassq_stats *ifqs)
{
	int error;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	switch (ifq->ifcq_type) {
	case PKTSCHEDT_TCQ:
		error = tcq_getqstats_ifclassq(ifq, qid, ifqs);
		break;

	case PKTSCHEDT_QFQ:
		error = qfq_getqstats_ifclassq(ifq, qid, ifqs);
		break;

	case PKTSCHEDT_FQ_CODEL:
		error = fq_if_getqstats_ifclassq(ifq, qid, ifqs);
		break;
	default:
		error = ENXIO;
		break;
	}

	return (error);
}