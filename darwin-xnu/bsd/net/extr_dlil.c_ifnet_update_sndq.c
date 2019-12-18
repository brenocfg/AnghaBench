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
struct tb_profile {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  tbr_percent; int /*<<< orphan*/  tbr_rate_raw; } ;
struct ifclassq {TYPE_1__ ifcq_tbr; } ;
typedef  int /*<<< orphan*/  cqev_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFCQ_IS_READY (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 scalar_t__ IFCQ_TBR_IS_ENABLED (struct ifclassq*) ; 
 int /*<<< orphan*/  ifclassq_tbr_set (struct ifclassq*,struct tb_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifclassq_update (struct ifclassq*,int /*<<< orphan*/ ) ; 

void
ifnet_update_sndq(struct ifclassq *ifq, cqev_t ev)
{
	IFCQ_LOCK_ASSERT_HELD(ifq);

	if (!(IFCQ_IS_READY(ifq)))
		return;

	if (IFCQ_TBR_IS_ENABLED(ifq)) {
		struct tb_profile tb = { ifq->ifcq_tbr.tbr_rate_raw,
		    ifq->ifcq_tbr.tbr_percent, 0 };
		(void) ifclassq_tbr_set(ifq, &tb, FALSE);
	}

	ifclassq_update(ifq, ev);
}