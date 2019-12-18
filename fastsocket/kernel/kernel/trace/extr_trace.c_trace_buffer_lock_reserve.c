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
struct trace_entry {int type; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;

/* Variables and functions */
 struct trace_entry* ring_buffer_event_data (struct ring_buffer_event*) ; 
 struct ring_buffer_event* ring_buffer_lock_reserve (struct ring_buffer*,unsigned long) ; 
 int /*<<< orphan*/  tracing_generic_entry_update (struct trace_entry*,unsigned long,int) ; 

struct ring_buffer_event *
trace_buffer_lock_reserve(struct ring_buffer *buffer,
			  int type,
			  unsigned long len,
			  unsigned long flags, int pc)
{
	struct ring_buffer_event *event;

	event = ring_buffer_lock_reserve(buffer, len);
	if (event != NULL) {
		struct trace_entry *ent = ring_buffer_event_data(event);

		tracing_generic_entry_update(ent, flags, pc);
		ent->type = type;
	}

	return event;
}