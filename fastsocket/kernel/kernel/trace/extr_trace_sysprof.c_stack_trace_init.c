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
 int /*<<< orphan*/  start_stack_timers () ; 
 struct trace_array* sysprof_trace ; 
 int tracer_enabled ; 
 int /*<<< orphan*/  tracing_start_cmdline_record () ; 

__attribute__((used)) static int stack_trace_init(struct trace_array *tr)
{
	sysprof_trace = tr;

	tracing_start_cmdline_record();

	mutex_lock(&sample_timer_lock);
	start_stack_timers();
	tracer_enabled = 1;
	mutex_unlock(&sample_timer_lock);
	return 0;
}