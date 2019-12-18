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
struct filter_type {TYPE_2__* filter; } ;
struct event_filter {int /*<<< orphan*/  filters; } ;
typedef  enum filter_trivial_type { ____Placeholder_filter_trivial_type } filter_trivial_type ;
struct TYPE_3__ {int value; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ boolean; } ;

/* Variables and functions */
 scalar_t__ FILTER_ARG_BOOLEAN ; 
#define  FILTER_TRIVIAL_FALSE 129 
#define  FILTER_TRIVIAL_TRUE 128 
 struct filter_type* find_filter_type (struct event_filter*,int) ; 

int pevent_filter_event_has_trivial(struct event_filter *filter,
				    int event_id,
				    enum filter_trivial_type type)
{
	struct filter_type *filter_type;

	if (!filter->filters)
		return 0;

	filter_type = find_filter_type(filter, event_id);

	if (!filter_type)
		return 0;

	if (filter_type->filter->type != FILTER_ARG_BOOLEAN)
		return 0;

	switch (type) {
	case FILTER_TRIVIAL_FALSE:
		return !filter_type->filter->boolean.value;

	case FILTER_TRIVIAL_TRUE:
		return filter_type->filter->boolean.value;
	default:
		return 1;
	}
}