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
struct filter_type {int dummy; } ;
struct event_filter {int filters; int /*<<< orphan*/ * event_filters; } ;

/* Variables and functions */
 struct filter_type* find_filter_type (struct event_filter*,int) ; 
 int /*<<< orphan*/  free_filter_type (struct filter_type*) ; 
 int /*<<< orphan*/  memmove (struct filter_type*,struct filter_type*,unsigned long) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int pevent_filter_remove_event(struct event_filter *filter,
			       int event_id)
{
	struct filter_type *filter_type;
	unsigned long len;

	if (!filter->filters)
		return 0;

	filter_type = find_filter_type(filter, event_id);

	if (!filter_type)
		return 0;

	free_filter_type(filter_type);

	/* The filter_type points into the event_filters array */
	len = (unsigned long)(filter->event_filters + filter->filters) -
		(unsigned long)(filter_type + 1);

	memmove(filter_type, filter_type + 1, len);
	filter->filters--;

	memset(&filter->event_filters[filter->filters], 0,
	       sizeof(*filter_type));

	return 1;
}