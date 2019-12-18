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
struct ftrace_graph_ret {int /*<<< orphan*/  rettime; } ;
struct TYPE_2__ {int /*<<< orphan*/  curr_ret_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ftrace_graph_return (struct ftrace_graph_ret*) ; 
 int /*<<< orphan*/  ftrace_graph_stop () ; 
 int /*<<< orphan*/  ftrace_pop_return_trace (struct ftrace_graph_ret*,unsigned long*,unsigned long) ; 
 scalar_t__ panic ; 
 int /*<<< orphan*/  trace_clock_local () ; 
 scalar_t__ unlikely (int) ; 

unsigned long ftrace_return_to_handler(unsigned long frame_pointer)
{
	struct ftrace_graph_ret trace;
	unsigned long ret;

	ftrace_pop_return_trace(&trace, &ret, frame_pointer);
	trace.rettime = trace_clock_local();
	ftrace_graph_return(&trace);
	barrier();
	current->curr_ret_stack--;

	if (unlikely(!ret)) {
		ftrace_graph_stop();
		WARN_ON(1);
		/* Might as well panic. What else to do? */
		ret = (unsigned long)panic;
	}

	return ret;
}