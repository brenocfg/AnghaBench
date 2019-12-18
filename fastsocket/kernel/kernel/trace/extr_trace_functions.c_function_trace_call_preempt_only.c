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

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 long atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftrace_function_enabled ; 
 int ftrace_preempt_disable () ; 
 int /*<<< orphan*/  ftrace_preempt_enable (int) ; 
 struct trace_array* func_trace ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int preempt_count () ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  trace_function (struct trace_array*,unsigned long,unsigned long,unsigned long,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
function_trace_call_preempt_only(unsigned long ip, unsigned long parent_ip)
{
	struct trace_array *tr = func_trace;
	struct trace_array_cpu *data;
	unsigned long flags;
	long disabled;
	int cpu, resched;
	int pc;

	if (unlikely(!ftrace_function_enabled))
		return;

	pc = preempt_count();
	resched = ftrace_preempt_disable();
	local_save_flags(flags);
	cpu = raw_smp_processor_id();
	data = tr->data[cpu];
	disabled = atomic_inc_return(&data->disabled);

	if (likely(disabled == 1))
		trace_function(tr, ip, parent_ip, flags, pc);

	atomic_dec(&data->disabled);
	ftrace_preempt_enable(resched);
}