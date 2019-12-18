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
struct ring_buffer_per_cpu {int /*<<< orphan*/  entries; } ;
struct ring_buffer_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_end_commit (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  rb_update_write_stamp (struct ring_buffer_per_cpu*,struct ring_buffer_event*) ; 

__attribute__((used)) static void rb_commit(struct ring_buffer_per_cpu *cpu_buffer,
		      struct ring_buffer_event *event)
{
	local_inc(&cpu_buffer->entries);
	rb_update_write_stamp(cpu_buffer, event);
	rb_end_commit(cpu_buffer);
}