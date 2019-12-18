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
struct pevent {int last_type; int nr_events; struct event_format** sort_events; int /*<<< orphan*/  events; } ;
struct event_format {int dummy; } ;
typedef  enum event_sort_type { ____Placeholder_event_sort_type } event_sort_type ;

/* Variables and functions */
#define  EVENT_SORT_ID 130 
#define  EVENT_SORT_NAME 129 
#define  EVENT_SORT_SYSTEM 128 
 int events_id_cmp (void const*,void const*) ; 
 int events_name_cmp (void const*,void const*) ; 
 int events_system_cmp (void const*,void const*) ; 
 struct event_format** malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct event_format**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsort (struct event_format**,size_t,int,int (*) (void const*,void const*)) ; 

struct event_format **pevent_list_events(struct pevent *pevent, enum event_sort_type sort_type)
{
	struct event_format **events;
	int (*sort)(const void *a, const void *b);

	events = pevent->sort_events;

	if (events && pevent->last_type == sort_type)
		return events;

	if (!events) {
		events = malloc(sizeof(*events) * (pevent->nr_events + 1));
		if (!events)
			return NULL;

		memcpy(events, pevent->events, sizeof(*events) * pevent->nr_events);
		events[pevent->nr_events] = NULL;

		pevent->sort_events = events;

		/* the internal events are sorted by id */
		if (sort_type == EVENT_SORT_ID) {
			pevent->last_type = sort_type;
			return events;
		}
	}

	switch (sort_type) {
	case EVENT_SORT_ID:
		sort = events_id_cmp;
		break;
	case EVENT_SORT_NAME:
		sort = events_name_cmp;
		break;
	case EVENT_SORT_SYSTEM:
		sort = events_system_cmp;
		break;
	default:
		return events;
	}

	qsort(events, pevent->nr_events, sizeof(*events), sort);
	pevent->last_type = sort_type;

	return events;
}