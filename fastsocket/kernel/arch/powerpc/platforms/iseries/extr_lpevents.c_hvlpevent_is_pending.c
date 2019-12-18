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
struct HvLpEvent {int dummy; } ;
struct TYPE_2__ {scalar_t__ hq_overflow_pending; scalar_t__ hq_current_event; } ;

/* Variables and functions */
 scalar_t__ hvlpevent_is_valid (struct HvLpEvent*) ; 
 TYPE_1__ hvlpevent_queue ; 
 scalar_t__ smp_processor_id () ; 
 scalar_t__ spread_lpevents ; 

int hvlpevent_is_pending(void)
{
	struct HvLpEvent *next_event;

	if (smp_processor_id() >= spread_lpevents)
		return 0;

	next_event = (struct HvLpEvent *)hvlpevent_queue.hq_current_event;

	return hvlpevent_is_valid(next_event) ||
		hvlpevent_queue.hq_overflow_pending;
}