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
 int /*<<< orphan*/  register_ftrace_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ops ; 
 int tracer_enabled ; 
 scalar_t__ tracing_is_enabled () ; 

__attribute__((used)) static void start_irqsoff_tracer(struct trace_array *tr)
{
	register_ftrace_function(&trace_ops);
	if (tracing_is_enabled())
		tracer_enabled = 1;
	else
		tracer_enabled = 0;
}