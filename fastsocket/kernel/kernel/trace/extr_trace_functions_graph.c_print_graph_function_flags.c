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
typedef  int /*<<< orphan*/  u32 ;
struct trace_iterator {int dummy; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_GRAPH_PRINT_ABS_TIME ; 
 int /*<<< orphan*/  TRACE_GRAPH_PRINT_DURATION ; 
 int TRACE_ITER_LATENCY_FMT ; 
 int __print_graph_function_flags (struct trace_iterator*,int /*<<< orphan*/ ) ; 
 int trace_flags ; 

enum print_line_t print_graph_function_flags(struct trace_iterator *iter,
					     u32 flags)
{
	if (trace_flags & TRACE_ITER_LATENCY_FMT)
		flags |= TRACE_GRAPH_PRINT_DURATION;
	else
		flags |= TRACE_GRAPH_PRINT_ABS_TIME;

	return __print_graph_function_flags(iter, flags);
}