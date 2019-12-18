#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct filter_type {int event_id; TYPE_2__* filter; } ;
struct event_filter {int filters; struct filter_type* event_filters; } ;
typedef  enum filter_trivial_type { ____Placeholder_filter_trivial_type } filter_trivial_type ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ boolean; } ;

/* Variables and functions */
 scalar_t__ FILTER_ARG_BOOLEAN ; 
#define  FILTER_TRIVIAL_FALSE 129 
#define  FILTER_TRIVIAL_TRUE 128 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  pevent_filter_remove_event (struct event_filter*,int) ; 
 int* realloc (int*,int) ; 

void pevent_filter_clear_trivial(struct event_filter *filter,
				 enum filter_trivial_type type)
{
	struct filter_type *filter_type;
	int count = 0;
	int *ids = NULL;
	int i;

	if (!filter->filters)
		return;

	/*
	 * Two steps, first get all ids with trivial filters.
	 *  then remove those ids.
	 */
	for (i = 0; i < filter->filters; i++) {
		filter_type = &filter->event_filters[i];
		if (filter_type->filter->type != FILTER_ARG_BOOLEAN)
			continue;
		switch (type) {
		case FILTER_TRIVIAL_FALSE:
			if (filter_type->filter->boolean.value)
				continue;
		case FILTER_TRIVIAL_TRUE:
			if (!filter_type->filter->boolean.value)
				continue;
		default:
			break;
		}

		ids = realloc(ids, sizeof(*ids) * (count + 1));
		if (!ids)
			die("Can't allocate ids");
		ids[count++] = filter_type->event_id;
	}

	if (!count)
		return;

	for (i = 0; i < count; i++)
		pevent_filter_remove_event(filter, ids[i]);

	free(ids);
}