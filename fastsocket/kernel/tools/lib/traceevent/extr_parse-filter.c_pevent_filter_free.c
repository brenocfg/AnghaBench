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
struct event_filter {int /*<<< orphan*/  pevent; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct event_filter*) ; 
 int /*<<< orphan*/  pevent_filter_reset (struct event_filter*) ; 
 int /*<<< orphan*/  pevent_unref (int /*<<< orphan*/ ) ; 

void pevent_filter_free(struct event_filter *filter)
{
	pevent_unref(filter->pevent);

	pevent_filter_reset(filter);

	free(filter);
}