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
struct qfq_if {int dummy; } ;
struct ifclassq {scalar_t__ ifcq_disc; } ;
typedef  int /*<<< orphan*/  cqrq_throttle_t ;
typedef  int cqrq_t ;
typedef  int /*<<< orphan*/  cqrq_stat_sc_t ;
typedef  int /*<<< orphan*/  cqrq_purge_sc_t ;
typedef  int /*<<< orphan*/  cqev_t ;

/* Variables and functions */
#define  CLASSQRQ_EVENT 132 
#define  CLASSQRQ_PURGE 131 
#define  CLASSQRQ_PURGE_SC 130 
#define  CLASSQRQ_STAT_SC 129 
#define  CLASSQRQ_THROTTLE 128 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int /*<<< orphan*/  qfq_event (struct qfq_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_purge (struct qfq_if*) ; 
 int /*<<< orphan*/  qfq_purge_sc (struct qfq_if*,int /*<<< orphan*/ *) ; 
 int qfq_stat_sc (struct qfq_if*,int /*<<< orphan*/ *) ; 
 int qfq_throttle (struct qfq_if*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qfq_request_ifclassq(struct ifclassq *ifq, cqrq_t req, void *arg)
{
	struct qfq_if *qif = (struct qfq_if *)ifq->ifcq_disc;
	int err = 0;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	switch (req) {
	case CLASSQRQ_PURGE:
		qfq_purge(qif);
		break;

	case CLASSQRQ_PURGE_SC:
		qfq_purge_sc(qif, (cqrq_purge_sc_t *)arg);
		break;

	case CLASSQRQ_EVENT:
		qfq_event(qif, (cqev_t)arg);
		break;

	case CLASSQRQ_THROTTLE:
		err = qfq_throttle(qif, (cqrq_throttle_t *)arg);
		break;
	case CLASSQRQ_STAT_SC:
		err = qfq_stat_sc(qif, (cqrq_stat_sc_t *)arg);
		break;
	}
	return (err);
}