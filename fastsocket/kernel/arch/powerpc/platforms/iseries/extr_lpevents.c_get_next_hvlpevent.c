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
struct HvLpEvent {int xSizeMinus1; } ;
struct TYPE_2__ {scalar_t__ hq_current_event; scalar_t__ hq_last_event; scalar_t__ hq_event_stack; } ;

/* Variables and functions */
 int IT_LP_EVENT_ALIGN ; 
 scalar_t__ hvlpevent_is_valid (struct HvLpEvent*) ; 
 TYPE_1__ hvlpevent_queue ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static struct HvLpEvent * get_next_hvlpevent(void)
{
	struct HvLpEvent * event;
	event = (struct HvLpEvent *)hvlpevent_queue.hq_current_event;

	if (hvlpevent_is_valid(event)) {
		/* rmb() needed only for weakly consistent machines (regatta) */
		rmb();
		/* Set pointer to next potential event */
		hvlpevent_queue.hq_current_event += ((event->xSizeMinus1 +
				IT_LP_EVENT_ALIGN) / IT_LP_EVENT_ALIGN) *
					IT_LP_EVENT_ALIGN;

		/* Wrap to beginning if no room at end */
		if (hvlpevent_queue.hq_current_event >
				hvlpevent_queue.hq_last_event) {
			hvlpevent_queue.hq_current_event =
				hvlpevent_queue.hq_event_stack;
		}
	} else {
		event = NULL;
	}

	return event;
}