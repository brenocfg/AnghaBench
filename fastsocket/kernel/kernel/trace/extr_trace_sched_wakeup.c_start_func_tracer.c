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
 int register_ftrace_function (int /*<<< orphan*/ *) ; 
 int register_ftrace_graph (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ops ; 
 int tracer_enabled ; 
 scalar_t__ tracing_is_enabled () ; 
 int /*<<< orphan*/  wakeup_graph_entry ; 
 int /*<<< orphan*/  wakeup_graph_return ; 

__attribute__((used)) static int start_func_tracer(int graph)
{
	int ret;

	if (!graph)
		ret = register_ftrace_function(&trace_ops);
	else
		ret = register_ftrace_graph(&wakeup_graph_return,
					    &wakeup_graph_entry);

	if (!ret && tracing_is_enabled())
		tracer_enabled = 1;
	else
		tracer_enabled = 0;

	return ret;
}