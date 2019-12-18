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
struct pevent {int nr_events; struct event_format** events; } ;
struct event_format {scalar_t__ id; struct pevent* pevent; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (struct event_format**,struct event_format**,int) ; 
 struct event_format** realloc (struct event_format**,int) ; 

__attribute__((used)) static int add_event(struct pevent *pevent, struct event_format *event)
{
	int i;
	struct event_format **events = realloc(pevent->events, sizeof(event) *
					       (pevent->nr_events + 1));
	if (!events)
		return -1;

	pevent->events = events;

	for (i = 0; i < pevent->nr_events; i++) {
		if (pevent->events[i]->id > event->id)
			break;
	}
	if (i < pevent->nr_events)
		memmove(&pevent->events[i + 1],
			&pevent->events[i],
			sizeof(event) * (pevent->nr_events - i));

	pevent->events[i] = event;
	pevent->nr_events++;

	event->pevent = pevent;

	return 0;
}