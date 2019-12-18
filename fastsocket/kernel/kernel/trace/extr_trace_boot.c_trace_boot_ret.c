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
struct boot_trace_ret {int /*<<< orphan*/  func; } ;
struct trace_boot_ret {struct boot_trace_ret boot_ret; } ;
struct trace_array {struct ring_buffer* buffer; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct ftrace_event_call {int dummy; } ;
typedef  scalar_t__ initcall_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_BOOT_RET ; 
 struct trace_array* boot_trace ; 
 struct ftrace_event_call event_boot_ret ; 
 int /*<<< orphan*/  filter_check_discard (struct ftrace_event_call*,struct trace_boot_ret*,struct ring_buffer*,struct ring_buffer_event*) ; 
 int /*<<< orphan*/  pre_initcalls_finished ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct trace_boot_ret* ring_buffer_event_data (struct ring_buffer_event*) ; 
 int /*<<< orphan*/  sprint_symbol (int /*<<< orphan*/ ,unsigned long) ; 
 struct ring_buffer_event* trace_buffer_lock_reserve (struct ring_buffer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_buffer_unlock_commit (struct ring_buffer*,struct ring_buffer_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void trace_boot_ret(struct boot_trace_ret *bt, initcall_t fn)
{
	struct ftrace_event_call *call = &event_boot_ret;
	struct ring_buffer_event *event;
	struct ring_buffer *buffer;
	struct trace_boot_ret *entry;
	struct trace_array *tr = boot_trace;

	if (!tr || !pre_initcalls_finished)
		return;

	sprint_symbol(bt->func, (unsigned long)fn);
	preempt_disable();

	buffer = tr->buffer;
	event = trace_buffer_lock_reserve(buffer, TRACE_BOOT_RET,
					  sizeof(*entry), 0, 0);
	if (!event)
		goto out;
	entry	= ring_buffer_event_data(event);
	entry->boot_ret = *bt;
	if (!filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit(buffer, event, 0, 0);
 out:
	preempt_enable();
}