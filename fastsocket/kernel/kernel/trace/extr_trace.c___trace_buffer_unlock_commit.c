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

/* Variables and functions */
 int /*<<< orphan*/  ftrace_trace_stack (struct ring_buffer*,unsigned long,int,int) ; 
 int /*<<< orphan*/  ftrace_trace_userstack (struct ring_buffer*,unsigned long,int) ; 
 int /*<<< orphan*/  ring_buffer_unlock_commit (struct ring_buffer*,struct ring_buffer_event*) ; 
 int /*<<< orphan*/  trace_wake_up () ; 

__attribute__((used)) static inline void
__trace_buffer_unlock_commit(struct ring_buffer *buffer,
			     struct ring_buffer_event *event,
			     unsigned long flags, int pc,
			     int wake)
{
	ring_buffer_unlock_commit(buffer, event);

	ftrace_trace_stack(buffer, flags, 6, pc);
	ftrace_trace_userstack(buffer, flags, pc);

	if (wake)
		trace_wake_up();
}