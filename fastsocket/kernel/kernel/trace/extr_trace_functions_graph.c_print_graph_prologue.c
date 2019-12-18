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
typedef  int u32 ;
struct trace_seq {int dummy; } ;
struct trace_iterator {int cpu; int /*<<< orphan*/  ts; struct trace_entry* ent; struct fgraph_data* private; } ;
struct trace_entry {int /*<<< orphan*/  pid; } ;
struct fgraph_data {int dummy; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int TRACE_GRAPH_PRINT_ABS_TIME ; 
 int TRACE_GRAPH_PRINT_CPU ; 
 int TRACE_GRAPH_PRINT_PROC ; 
 int TRACE_ITER_LATENCY_FMT ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 int print_graph_abs_time (int /*<<< orphan*/ ,struct trace_seq*) ; 
 int print_graph_cpu (struct trace_seq*,int) ; 
 int print_graph_irq (struct trace_iterator*,unsigned long,int,int,int /*<<< orphan*/ ,int) ; 
 int print_graph_lat_fmt (struct trace_seq*,struct trace_entry*) ; 
 int print_graph_proc (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int trace_flags ; 
 int trace_seq_printf (struct trace_seq*,char*) ; 
 int verif_pid (struct trace_seq*,int /*<<< orphan*/ ,int,struct fgraph_data*) ; 

__attribute__((used)) static enum print_line_t
print_graph_prologue(struct trace_iterator *iter, struct trace_seq *s,
		     int type, unsigned long addr, u32 flags)
{
	struct fgraph_data *data = iter->private;
	struct trace_entry *ent = iter->ent;
	int cpu = iter->cpu;
	int ret;

	/* Pid */
	if (verif_pid(s, ent->pid, cpu, data) == TRACE_TYPE_PARTIAL_LINE)
		return TRACE_TYPE_PARTIAL_LINE;

	if (type) {
		/* Interrupt */
		ret = print_graph_irq(iter, addr, type, cpu, ent->pid, flags);
		if (ret == TRACE_TYPE_PARTIAL_LINE)
			return TRACE_TYPE_PARTIAL_LINE;
	}

	/* Absolute time */
	if (flags & TRACE_GRAPH_PRINT_ABS_TIME) {
		ret = print_graph_abs_time(iter->ts, s);
		if (!ret)
			return TRACE_TYPE_PARTIAL_LINE;
	}

	/* Cpu */
	if (flags & TRACE_GRAPH_PRINT_CPU) {
		ret = print_graph_cpu(s, cpu);
		if (ret == TRACE_TYPE_PARTIAL_LINE)
			return TRACE_TYPE_PARTIAL_LINE;
	}

	/* Proc */
	if (flags & TRACE_GRAPH_PRINT_PROC) {
		ret = print_graph_proc(s, ent->pid);
		if (ret == TRACE_TYPE_PARTIAL_LINE)
			return TRACE_TYPE_PARTIAL_LINE;

		ret = trace_seq_printf(s, " | ");
		if (!ret)
			return TRACE_TYPE_PARTIAL_LINE;
	}

	/* Latency format */
	if (trace_flags & TRACE_ITER_LATENCY_FMT) {
		ret = print_graph_lat_fmt(s, ent);
		if (ret == TRACE_TYPE_PARTIAL_LINE)
			return TRACE_TYPE_PARTIAL_LINE;
	}

	return 0;
}