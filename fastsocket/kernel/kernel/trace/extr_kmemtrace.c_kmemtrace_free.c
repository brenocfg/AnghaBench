#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct trace_array {int /*<<< orphan*/  buffer; } ;
struct ring_buffer_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct kmemtrace_free_entry {int type_id; unsigned long call_site; void const* ptr; TYPE_1__ ent; } ;
struct ftrace_event_call {int dummy; } ;
typedef  enum kmemtrace_type_id { ____Placeholder_kmemtrace_type_id } kmemtrace_type_id ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_KMEM_FREE ; 
 struct ftrace_event_call event_kmem_free ; 
 int /*<<< orphan*/  filter_check_discard (struct ftrace_event_call*,struct kmemtrace_free_entry*,int /*<<< orphan*/ ,struct ring_buffer_event*) ; 
 struct trace_array* kmemtrace_array ; 
 struct kmemtrace_free_entry* ring_buffer_event_data (struct ring_buffer_event*) ; 
 struct ring_buffer_event* ring_buffer_lock_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ring_buffer_unlock_commit (int /*<<< orphan*/ ,struct ring_buffer_event*) ; 
 int /*<<< orphan*/  trace_wake_up () ; 
 int /*<<< orphan*/  tracing_generic_entry_update (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void kmemtrace_free(enum kmemtrace_type_id type_id,
				  unsigned long call_site,
				  const void *ptr)
{
	struct ftrace_event_call *call = &event_kmem_free;
	struct trace_array *tr = kmemtrace_array;
	struct kmemtrace_free_entry *entry;
	struct ring_buffer_event *event;

	event = ring_buffer_lock_reserve(tr->buffer, sizeof(*entry));
	if (!event)
		return;
	entry	= ring_buffer_event_data(event);
	tracing_generic_entry_update(&entry->ent, 0, 0);

	entry->ent.type		= TRACE_KMEM_FREE;
	entry->type_id		= type_id;
	entry->call_site	= call_site;
	entry->ptr		= ptr;

	if (!filter_check_discard(call, entry, tr->buffer, event))
		ring_buffer_unlock_commit(tr->buffer, event);

	trace_wake_up();
}