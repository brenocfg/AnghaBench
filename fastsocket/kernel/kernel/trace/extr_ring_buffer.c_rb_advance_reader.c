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
struct ring_buffer_per_cpu {TYPE_1__* reader_page; int /*<<< orphan*/  read; } ;
struct ring_buffer_event {scalar_t__ type_len; } ;
struct buffer_page {int dummy; } ;
struct TYPE_2__ {unsigned int read; } ;

/* Variables and functions */
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,int) ; 
 scalar_t__ RINGBUF_TYPE_DATA_TYPE_LEN_MAX ; 
 unsigned int rb_event_length (struct ring_buffer_event*) ; 
 struct buffer_page* rb_get_reader_page (struct ring_buffer_per_cpu*) ; 
 struct ring_buffer_event* rb_reader_event (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  rb_update_read_stamp (struct ring_buffer_per_cpu*,struct ring_buffer_event*) ; 

__attribute__((used)) static void rb_advance_reader(struct ring_buffer_per_cpu *cpu_buffer)
{
	struct ring_buffer_event *event;
	struct buffer_page *reader;
	unsigned length;

	reader = rb_get_reader_page(cpu_buffer);

	/* This function should not be called when buffer is empty */
	if (RB_WARN_ON(cpu_buffer, !reader))
		return;

	event = rb_reader_event(cpu_buffer);

	if (event->type_len <= RINGBUF_TYPE_DATA_TYPE_LEN_MAX)
		cpu_buffer->read++;

	rb_update_read_stamp(cpu_buffer, event);

	length = rb_event_length(event);
	cpu_buffer->reader_page->read += length;
}