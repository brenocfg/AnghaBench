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
struct mmiotrace_map {int dummy; } ;
struct trace_mmiotrace_map {struct mmiotrace_map map; } ;
struct trace_array_cpu {int dummy; } ;
struct trace_array {struct ring_buffer* buffer; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct ftrace_event_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_MMIO_MAP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dropped_count ; 
 struct ftrace_event_call event_mmiotrace_map ; 
 int /*<<< orphan*/  filter_check_discard (struct ftrace_event_call*,struct trace_mmiotrace_map*,struct ring_buffer*,struct ring_buffer_event*) ; 
 int preempt_count () ; 
 struct trace_mmiotrace_map* ring_buffer_event_data (struct ring_buffer_event*) ; 
 struct ring_buffer_event* trace_buffer_lock_reserve (struct ring_buffer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_buffer_unlock_commit (struct ring_buffer*,struct ring_buffer_event*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __trace_mmiotrace_map(struct trace_array *tr,
				struct trace_array_cpu *data,
				struct mmiotrace_map *map)
{
	struct ftrace_event_call *call = &event_mmiotrace_map;
	struct ring_buffer *buffer = tr->buffer;
	struct ring_buffer_event *event;
	struct trace_mmiotrace_map *entry;
	int pc = preempt_count();

	event = trace_buffer_lock_reserve(buffer, TRACE_MMIO_MAP,
					  sizeof(*entry), 0, pc);
	if (!event) {
		atomic_inc(&dropped_count);
		return;
	}
	entry	= ring_buffer_event_data(event);
	entry->map			= *map;

	if (!filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit(buffer, event, 0, pc);
}