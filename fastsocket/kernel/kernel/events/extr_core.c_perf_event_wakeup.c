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
struct perf_event {scalar_t__ pending_kill; int /*<<< orphan*/  fasync; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ring_buffer_wakeup (struct perf_event*) ; 

void perf_event_wakeup(struct perf_event *event)
{
	ring_buffer_wakeup(event);

	if (event->pending_kill) {
		kill_fasync(&event->fasync, SIGIO, event->pending_kill);
		event->pending_kill = 0;
	}
}