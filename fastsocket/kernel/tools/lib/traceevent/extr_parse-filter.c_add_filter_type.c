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
struct filter_type {int event_id; int /*<<< orphan*/ * filter; int /*<<< orphan*/  event; } ;
struct event_filter {int filters; int /*<<< orphan*/  pevent; struct filter_type* event_filters; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 struct filter_type* find_filter_type (struct event_filter*,int) ; 
 int /*<<< orphan*/  memmove (struct filter_type*,struct filter_type*,int) ; 
 int /*<<< orphan*/  pevent_find_event (int /*<<< orphan*/ ,int) ; 
 struct filter_type* realloc (struct filter_type*,int) ; 

__attribute__((used)) static struct filter_type *
add_filter_type(struct event_filter *filter, int id)
{
	struct filter_type *filter_type;
	int i;

	filter_type = find_filter_type(filter, id);
	if (filter_type)
		return filter_type;

	filter->event_filters =	realloc(filter->event_filters,
					sizeof(*filter->event_filters) *
					(filter->filters + 1));
	if (!filter->event_filters)
		die("Could not allocate filter");

	for (i = 0; i < filter->filters; i++) {
		if (filter->event_filters[i].event_id > id)
			break;
	}

	if (i < filter->filters)
		memmove(&filter->event_filters[i+1],
			&filter->event_filters[i],
			sizeof(*filter->event_filters) *
			(filter->filters - i));

	filter_type = &filter->event_filters[i];
	filter_type->event_id = id;
	filter_type->event = pevent_find_event(filter->pevent, id);
	filter_type->filter = NULL;

	filter->filters++;

	return filter_type;
}