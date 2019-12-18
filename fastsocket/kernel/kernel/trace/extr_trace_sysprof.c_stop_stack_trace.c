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
struct trace_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sample_timer_lock ; 
 int /*<<< orphan*/  stop_stack_timers () ; 
 scalar_t__ tracer_enabled ; 

__attribute__((used)) static void stop_stack_trace(struct trace_array *tr)
{
	mutex_lock(&sample_timer_lock);
	stop_stack_timers();
	tracer_enabled = 0;
	mutex_unlock(&sample_timer_lock);
}