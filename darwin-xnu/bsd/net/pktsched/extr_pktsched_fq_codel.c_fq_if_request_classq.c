#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ifclassq {scalar_t__ ifcq_disc; } ;
struct TYPE_7__ {int /*<<< orphan*/  fqs_ifq; } ;
typedef  TYPE_1__ fq_if_t ;
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
 int /*<<< orphan*/  IFCQ_CONVERT_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int /*<<< orphan*/  fq_if_event (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_if_purge (TYPE_1__*) ; 
 int /*<<< orphan*/  fq_if_purge_sc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fq_if_stat_sc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fq_if_throttle (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
fq_if_request_classq(struct ifclassq *ifq, cqrq_t rq, void *arg)
{
	int err = 0;
	fq_if_t *fqs = (fq_if_t *)ifq->ifcq_disc;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	/*
	 * These are usually slow operations, convert the lock ahead of time
	 */
	IFCQ_CONVERT_LOCK(fqs->fqs_ifq);
	switch (rq) {
	case CLASSQRQ_PURGE:
		fq_if_purge(fqs);
		break;
	case CLASSQRQ_PURGE_SC:
		fq_if_purge_sc(fqs, (cqrq_purge_sc_t *)arg);
		break;
	case CLASSQRQ_EVENT:
		fq_if_event(fqs, (cqev_t)arg);
		break;
	case CLASSQRQ_THROTTLE:
		fq_if_throttle(fqs, (cqrq_throttle_t *)arg);
		break;
	case CLASSQRQ_STAT_SC:
		fq_if_stat_sc(fqs, (cqrq_stat_sc_t *)arg);
		break;
	}
	return (err);
}