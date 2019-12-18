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
struct trace_seq {int dummy; } ;
struct event_subsystem {struct event_filter* filter; } ;
struct event_filter {scalar_t__ filter_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 

void print_subsystem_event_filter(struct event_subsystem *system,
				  struct trace_seq *s)
{
	struct event_filter *filter = system->filter;

	mutex_lock(&event_mutex);
	if (filter && filter->filter_string)
		trace_seq_printf(s, "%s\n", filter->filter_string);
	else
		trace_seq_printf(s, "none\n");
	mutex_unlock(&event_mutex);
}