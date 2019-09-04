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
typedef  scalar_t__ u_int64_t ;
struct ifnet {int if_eflags; scalar_t__ if_start_delay_timeout; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 scalar_t__ IFCQ_TARGET_QDELAY (int /*<<< orphan*/ *) ; 
 int IFEF_ENQUEUE_MULTI ; 
 scalar_t__ IFQ_TARGET_DELAY ; 
 scalar_t__ ifclassq_target_qdelay ; 

void
ifclassq_calc_target_qdelay(struct ifnet *ifp, u_int64_t *if_target_qdelay)
{
	u_int64_t qdelay = 0;
	qdelay = IFCQ_TARGET_QDELAY(&ifp->if_snd);

	if (ifclassq_target_qdelay != 0)
		qdelay = ifclassq_target_qdelay;

	/*
	 * If we do not know the effective bandwidth, use the default
	 * target queue delay.
	 */
	if (qdelay == 0)
		qdelay = IFQ_TARGET_DELAY;

	/*
	 * If a delay has been added to ifnet start callback for
	 * coalescing, we have to add that to the pre-set target delay
	 * because the packets can be in the queue longer.
	 */
	if ((ifp->if_eflags & IFEF_ENQUEUE_MULTI) &&
	    ifp->if_start_delay_timeout > 0)
		qdelay += ifp->if_start_delay_timeout;

	*(if_target_qdelay) = qdelay;
}