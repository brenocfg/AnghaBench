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
struct event_filter {int filters; int /*<<< orphan*/ * event_filters; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_filter_type (int /*<<< orphan*/ *) ; 

void pevent_filter_reset(struct event_filter *filter)
{
	int i;

	for (i = 0; i < filter->filters; i++)
		free_filter_type(&filter->event_filters[i]);

	free(filter->event_filters);
	filter->filters = 0;
	filter->event_filters = NULL;
}