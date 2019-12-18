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
struct ftrace_graph_ent {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int __trace_graph_entry (struct trace_array*,struct ftrace_graph_ent*,unsigned long,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 long atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ftrace_graph_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftrace_trace_task (int /*<<< orphan*/ ) ; 
 struct trace_array* graph_array ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int preempt_count () ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  set_tsk_trace_graph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_tsk_trace_graph (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int trace_graph_entry(struct ftrace_graph_ent *trace)
{
	struct trace_array *tr = graph_array;
	struct trace_array_cpu *data;
	unsigned long flags;
	long disabled;
	int ret;
	int cpu;
	int pc;

	if (unlikely(!tr))
		return 0;

	if (!ftrace_trace_task(current))
		return 0;

	if (!ftrace_graph_addr(trace->func))
		return 0;

	local_irq_save(flags);
	cpu = raw_smp_processor_id();
	data = tr->data[cpu];
	disabled = atomic_inc_return(&data->disabled);
	if (likely(disabled == 1)) {
		pc = preempt_count();
		ret = __trace_graph_entry(tr, trace, flags, pc);
	} else {
		ret = 0;
	}
	/* Only do the atomic if it is not already set */
	if (!test_tsk_trace_graph(current))
		set_tsk_trace_graph(current);

	atomic_dec(&data->disabled);
	local_irq_restore(flags);

	return ret;
}