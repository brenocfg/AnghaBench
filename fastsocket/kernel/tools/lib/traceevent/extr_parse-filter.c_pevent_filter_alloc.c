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
struct pevent {int dummy; } ;
struct event_filter {struct pevent* pevent; } ;

/* Variables and functions */
 struct event_filter* malloc_or_die (int) ; 
 int /*<<< orphan*/  memset (struct event_filter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pevent_ref (struct pevent*) ; 

struct event_filter *pevent_filter_alloc(struct pevent *pevent)
{
	struct event_filter *filter;

	filter = malloc_or_die(sizeof(*filter));
	memset(filter, 0, sizeof(*filter));
	filter->pevent = pevent;
	pevent_ref(pevent);

	return filter;
}