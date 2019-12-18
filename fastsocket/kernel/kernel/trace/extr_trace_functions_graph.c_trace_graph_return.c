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
struct trace_array_cpu {int /*<<< orphan*/  disabled; } ;
struct trace_array {struct trace_array_cpu** data; } ;
struct ftrace_graph_ret {int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trace_graph_return (struct trace_array*,struct ftrace_graph_ret*,unsigned long,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 long atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_tsk_trace_graph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 struct trace_array* graph_array ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int preempt_count () ; 
 int raw_smp_processor_id () ; 

void trace_graph_return(struct ftrace_graph_ret *trace)
{
	struct trace_array *tr = graph_array;
	struct trace_array_cpu *data;
	unsigned long flags;
	long disabled;
	int cpu;
	int pc;

	local_irq_save(flags);
	cpu = raw_smp_processor_id();
	data = tr->data[cpu];
	disabled = atomic_inc_return(&data->disabled);
	if (likely(disabled == 1)) {
		pc = preempt_count();
		__trace_graph_return(tr, trace, flags, pc);
	}
	if (!trace->depth)
		clear_tsk_trace_graph(current);
	atomic_dec(&data->disabled);
	local_irq_restore(flags);
}