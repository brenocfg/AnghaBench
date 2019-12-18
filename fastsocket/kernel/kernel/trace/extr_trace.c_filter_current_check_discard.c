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
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct ftrace_event_call {int dummy; } ;

/* Variables and functions */
 int filter_check_discard (struct ftrace_event_call*,void*,struct ring_buffer*,struct ring_buffer_event*) ; 

int filter_current_check_discard(struct ring_buffer *buffer,
				 struct ftrace_event_call *call, void *rec,
				 struct ring_buffer_event *event)
{
	return filter_check_discard(call, rec, buffer, event);
}