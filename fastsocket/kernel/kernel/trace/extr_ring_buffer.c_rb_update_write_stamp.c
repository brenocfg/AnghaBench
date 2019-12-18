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
struct ring_buffer_per_cpu {int /*<<< orphan*/  write_stamp; } ;
struct ring_buffer_event {scalar_t__ time_delta; } ;

/* Variables and functions */
 scalar_t__ rb_event_is_commit (struct ring_buffer_per_cpu*,struct ring_buffer_event*) ; 

__attribute__((used)) static void
rb_update_write_stamp(struct ring_buffer_per_cpu *cpu_buffer,
		      struct ring_buffer_event *event)
{
	/*
	 * The event first in the commit queue updates the
	 * time stamp.
	 */
	if (rb_event_is_commit(cpu_buffer, event))
		cpu_buffer->write_stamp += event->time_delta;
}