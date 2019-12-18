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
 int /*<<< orphan*/  trace_ops ; 
 scalar_t__ tracer_enabled ; 
 int /*<<< orphan*/  unregister_ftrace_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_ftrace_graph () ; 

__attribute__((used)) static void stop_func_tracer(int graph)
{
	tracer_enabled = 0;

	if (!graph)
		unregister_ftrace_function(&trace_ops);
	else
		unregister_ftrace_graph();
}