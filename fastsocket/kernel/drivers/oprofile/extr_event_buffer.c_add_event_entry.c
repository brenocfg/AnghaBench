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
struct TYPE_2__ {int /*<<< orphan*/  event_lost_overflow; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 size_t buffer_pos ; 
 int /*<<< orphan*/  buffer_ready ; 
 size_t buffer_size ; 
 int /*<<< orphan*/  buffer_wait ; 
 size_t buffer_watershed ; 
 unsigned long* event_buffer ; 
 TYPE_1__ oprofile_stats ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void add_event_entry(unsigned long value)
{
	/*
	 * This shouldn't happen since all workqueues or handlers are
	 * canceled or flushed before the event buffer is freed.
	 */
	if (!event_buffer) {
		WARN_ON_ONCE(1);
		return;
	}

	if (buffer_pos == buffer_size) {
		atomic_inc(&oprofile_stats.event_lost_overflow);
		return;
	}

	event_buffer[buffer_pos] = value;
	if (++buffer_pos == buffer_size - buffer_watershed) {
		atomic_set(&buffer_ready, 1);
		wake_up(&buffer_wait);
	}
}