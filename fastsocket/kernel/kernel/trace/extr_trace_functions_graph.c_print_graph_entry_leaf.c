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
typedef  int u32 ;
struct trace_seq {int dummy; } ;
struct trace_iterator {int cpu; struct fgraph_data* private; } ;
struct ftrace_graph_ret {unsigned long long rettime; unsigned long long calltime; } ;
struct ftrace_graph_ret_entry {struct ftrace_graph_ret ret; } ;
struct ftrace_graph_ent {int depth; scalar_t__ func; } ;
struct ftrace_graph_ent_entry {struct ftrace_graph_ent graph_ent; } ;
struct fgraph_data {int dummy; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 int TRACE_GRAPH_INDENT ; 
 int TRACE_GRAPH_PRINT_DURATION ; 
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 TYPE_1__* per_cpu_ptr (struct fgraph_data*,int) ; 
 int print_graph_duration (unsigned long long,struct trace_seq*) ; 
 int print_graph_overhead (unsigned long long,struct trace_seq*,int) ; 
 int trace_seq_printf (struct trace_seq*,char*,...) ; 

__attribute__((used)) static enum print_line_t
print_graph_entry_leaf(struct trace_iterator *iter,
		struct ftrace_graph_ent_entry *entry,
		struct ftrace_graph_ret_entry *ret_entry,
		struct trace_seq *s, u32 flags)
{
	struct fgraph_data *data = iter->private;
	struct ftrace_graph_ret *graph_ret;
	struct ftrace_graph_ent *call;
	unsigned long long duration;
	int ret;
	int i;

	graph_ret = &ret_entry->ret;
	call = &entry->graph_ent;
	duration = graph_ret->rettime - graph_ret->calltime;

	if (data) {
		int cpu = iter->cpu;
		int *depth = &(per_cpu_ptr(data, cpu)->depth);

		/*
		 * Comments display at + 1 to depth. Since
		 * this is a leaf function, keep the comments
		 * equal to this depth.
		 */
		*depth = call->depth - 1;
	}

	/* Overhead */
	ret = print_graph_overhead(duration, s, flags);
	if (!ret)
		return TRACE_TYPE_PARTIAL_LINE;

	/* Duration */
	if (flags & TRACE_GRAPH_PRINT_DURATION) {
		ret = print_graph_duration(duration, s);
		if (ret == TRACE_TYPE_PARTIAL_LINE)
			return TRACE_TYPE_PARTIAL_LINE;
	}

	/* Function */
	for (i = 0; i < call->depth * TRACE_GRAPH_INDENT; i++) {
		ret = trace_seq_printf(s, " ");
		if (!ret)
			return TRACE_TYPE_PARTIAL_LINE;
	}

	ret = trace_seq_printf(s, "%ps();\n", (void *)call->func);
	if (!ret)
		return TRACE_TYPE_PARTIAL_LINE;

	return TRACE_TYPE_HANDLED;
}