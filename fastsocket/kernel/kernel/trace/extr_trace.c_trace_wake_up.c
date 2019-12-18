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

/* Variables and functions */
 int TRACE_ITER_BLOCK ; 
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  runqueue_is_locked (int) ; 
 int trace_flags ; 
 int /*<<< orphan*/  trace_wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void trace_wake_up(void)
{
	int cpu;

	if (trace_flags & TRACE_ITER_BLOCK)
		return;
	/*
	 * The runqueue_is_locked() can fail, but this is the best we
	 * have for now:
	 */
	cpu = get_cpu();
	if (!runqueue_is_locked(cpu))
		wake_up(&trace_wait);
	put_cpu();
}