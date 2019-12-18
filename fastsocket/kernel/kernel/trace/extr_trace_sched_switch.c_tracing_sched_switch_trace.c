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
struct trace_array {struct ring_buffer* buffer; } ;
struct task_struct {int /*<<< orphan*/  state; int /*<<< orphan*/  prio; int /*<<< orphan*/  pid; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct ftrace_event_call {int dummy; } ;
struct ctx_switch_entry {int /*<<< orphan*/  next_cpu; int /*<<< orphan*/  next_state; int /*<<< orphan*/  next_prio; int /*<<< orphan*/  next_pid; int /*<<< orphan*/  prev_state; int /*<<< orphan*/  prev_prio; int /*<<< orphan*/  prev_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_CTX ; 
 struct ftrace_event_call event_context_switch ; 
 int /*<<< orphan*/  filter_check_discard (struct ftrace_event_call*,struct ctx_switch_entry*,struct ring_buffer*,struct ring_buffer_event*) ; 
 struct ctx_switch_entry* ring_buffer_event_data (struct ring_buffer_event*) ; 
 int /*<<< orphan*/  task_cpu (struct task_struct*) ; 
 struct ring_buffer_event* trace_buffer_lock_reserve (struct ring_buffer*,int /*<<< orphan*/ ,int,unsigned long,int) ; 
 int /*<<< orphan*/  trace_buffer_unlock_commit (struct ring_buffer*,struct ring_buffer_event*,unsigned long,int) ; 

void
tracing_sched_switch_trace(struct trace_array *tr,
			   struct task_struct *prev,
			   struct task_struct *next,
			   unsigned long flags, int pc)
{
	struct ftrace_event_call *call = &event_context_switch;
	struct ring_buffer *buffer = tr->buffer;
	struct ring_buffer_event *event;
	struct ctx_switch_entry *entry;

	event = trace_buffer_lock_reserve(buffer, TRACE_CTX,
					  sizeof(*entry), flags, pc);
	if (!event)
		return;
	entry	= ring_buffer_event_data(event);
	entry->prev_pid			= prev->pid;
	entry->prev_prio		= prev->prio;
	entry->prev_state		= prev->state;
	entry->next_pid			= next->pid;
	entry->next_prio		= next->prio;
	entry->next_state		= next->state;
	entry->next_cpu	= task_cpu(next);

	if (!filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit(buffer, event, flags, pc);
}