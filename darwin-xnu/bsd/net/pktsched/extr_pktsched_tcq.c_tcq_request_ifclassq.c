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
struct tcq_if {int dummy; } ;
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
 int /*<<< orphan*/  tcq_event (struct tcq_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcq_purge (struct tcq_if*) ; 
 int /*<<< orphan*/  tcq_purge_sc (struct tcq_if*,int /*<<< orphan*/ *) ; 
 int tcq_stat_sc (struct tcq_if*,int /*<<< orphan*/ *) ; 
 int tcq_throttle (struct tcq_if*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tcq_request_ifclassq(struct ifclassq *ifq, cqrq_t req, void *arg)
{
	struct tcq_if	*tif = (struct tcq_if *)ifq->ifcq_disc;
	int err = 0;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	switch (req) {
	case CLASSQRQ_PURGE:
		tcq_purge(tif);
		break;

	case CLASSQRQ_PURGE_SC:
		tcq_purge_sc(tif, (cqrq_purge_sc_t *)arg);
		break;

	case CLASSQRQ_EVENT:
		tcq_event(tif, (cqev_t)arg);
		break;

	case CLASSQRQ_THROTTLE:
		err = tcq_throttle(tif, (cqrq_throttle_t *)arg);
		break;

	case CLASSQRQ_STAT_SC:
		err = tcq_stat_sc(tif, (cqrq_stat_sc_t *)arg);
		break;
	}
	return (err);
}