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
 struct trace_array* graph_array ; 
 int register_ftrace_graph (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_graph_entry ; 
 int /*<<< orphan*/  trace_graph_return ; 
 int /*<<< orphan*/  tracing_start_cmdline_record () ; 

__attribute__((used)) static int graph_trace_init(struct trace_array *tr)
{
	int ret;

	graph_array = tr;
	ret = register_ftrace_graph(&trace_graph_return,
				    &trace_graph_entry);
	if (ret)
		return ret;
	tracing_start_cmdline_record();

	return 0;
}