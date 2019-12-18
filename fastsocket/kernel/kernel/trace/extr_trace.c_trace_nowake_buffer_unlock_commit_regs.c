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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftrace_trace_stack_regs (struct ring_buffer*,unsigned long,int /*<<< orphan*/ ,int,struct pt_regs*) ; 
 int /*<<< orphan*/  ftrace_trace_userstack (struct ring_buffer*,unsigned long,int) ; 
 int /*<<< orphan*/  ring_buffer_unlock_commit (struct ring_buffer*,struct ring_buffer_event*) ; 

void trace_nowake_buffer_unlock_commit_regs(struct ring_buffer *buffer,
					    struct ring_buffer_event *event,
					    unsigned long flags, int pc,
					    struct pt_regs *regs)
{
	ring_buffer_unlock_commit(buffer, event);

	ftrace_trace_stack_regs(buffer, flags, 0, pc, regs);
	ftrace_trace_userstack(buffer, flags, pc);
}