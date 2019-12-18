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
struct filter_type {int /*<<< orphan*/  filter; } ;
struct event_filter {int /*<<< orphan*/  filters; } ;

/* Variables and functions */
 char* arg_to_str (struct event_filter*,int /*<<< orphan*/ ) ; 
 struct filter_type* find_filter_type (struct event_filter*,int) ; 

char *
pevent_filter_make_string(struct event_filter *filter, int event_id)
{
	struct filter_type *filter_type;

	if (!filter->filters)
		return NULL;

	filter_type = find_filter_type(filter, event_id);

	if (!filter_type)
		return NULL;

	return arg_to_str(filter, filter_type->filter);
}