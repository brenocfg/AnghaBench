#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ifclassq {int dummy; } ;
struct TYPE_8__ {int fqs_throttle; int /*<<< orphan*/ * fqs_classq; struct ifclassq* fqs_ifq; } ;
typedef  TYPE_1__ fq_if_t ;
struct TYPE_9__ {int level; int /*<<< orphan*/  set; } ;
typedef  TYPE_2__ cqrq_throttle_t ;

/* Variables and functions */
 int EALREADY ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
#define  IFNET_THROTTLE_OFF 129 
#define  IFNET_THROTTLE_OPPORTUNISTIC 128 
 int /*<<< orphan*/  MBUF_SC_BK_SYS ; 
 int /*<<< orphan*/  fq_if_classq_resume (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fq_if_classq_suspend (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int fq_if_service_to_priority (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fq_if_throttle(fq_if_t *fqs, cqrq_throttle_t *tr)
{
	struct ifclassq *ifq = fqs->fqs_ifq;
	int index;
#if !MACH_ASSERT
#pragma unused(ifq)
#endif
	IFCQ_LOCK_ASSERT_HELD(ifq);

	if (!tr->set) {
		tr->level = fqs->fqs_throttle;
		return (0);
	}

	if (tr->level == fqs->fqs_throttle)
		return (EALREADY);

	/* Throttling is allowed on BK_SYS class only */
	index = fq_if_service_to_priority(fqs, MBUF_SC_BK_SYS);
	switch (tr->level) {
	case IFNET_THROTTLE_OFF:
		fq_if_classq_resume(fqs, &fqs->fqs_classq[index]);
		break;
	case IFNET_THROTTLE_OPPORTUNISTIC:
		fq_if_classq_suspend(fqs, &fqs->fqs_classq[index]);
		break;
	default:
		break;
	}
	return (0);
}