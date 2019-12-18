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
struct pevent {int nr_events; struct event_format* last_event; struct event_format** events; } ;
struct event_format {int /*<<< orphan*/  system; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct event_format *
pevent_find_event_by_name(struct pevent *pevent,
			  const char *sys, const char *name)
{
	struct event_format *event;
	int i;

	if (pevent->last_event &&
	    strcmp(pevent->last_event->name, name) == 0 &&
	    (!sys || strcmp(pevent->last_event->system, sys) == 0))
		return pevent->last_event;

	for (i = 0; i < pevent->nr_events; i++) {
		event = pevent->events[i];
		if (strcmp(event->name, name) == 0) {
			if (!sys)
				break;
			if (strcmp(event->system, sys) == 0)
				break;
		}
	}
	if (i == pevent->nr_events)
		event = NULL;

	pevent->last_event = event;
	return event;
}