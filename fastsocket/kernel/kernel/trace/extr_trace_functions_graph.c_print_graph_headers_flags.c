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
struct seq_file {struct trace_iterator* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_GRAPH_PRINT_ABS_TIME ; 
 int /*<<< orphan*/  TRACE_GRAPH_PRINT_DURATION ; 
 int TRACE_ITER_LATENCY_FMT ; 
 int /*<<< orphan*/  __print_graph_headers_flags (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_trace_header (struct seq_file*,struct trace_iterator*) ; 
 scalar_t__ trace_empty (struct trace_iterator*) ; 
 int trace_flags ; 

void print_graph_headers_flags(struct seq_file *s, u32 flags)
{
	struct trace_iterator *iter = s->private;

	if (trace_flags & TRACE_ITER_LATENCY_FMT) {
		/* print nothing if the buffers are empty */
		if (trace_empty(iter))
			return;

		print_trace_header(s, iter);
		flags |= TRACE_GRAPH_PRINT_DURATION;
	} else
		flags |= TRACE_GRAPH_PRINT_ABS_TIME;

	__print_graph_headers_flags(s, flags);
}