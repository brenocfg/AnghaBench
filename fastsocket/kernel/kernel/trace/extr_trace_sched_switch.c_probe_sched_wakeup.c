#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trace_array_cpu {int /*<<< orphan*/  disabled; } ;
struct task_struct {int dummy; } ;
struct rq {int dummy; } ;
struct TYPE_3__ {struct trace_array_cpu** data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* ctx_trace ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int preempt_count () ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  sched_ref ; 
 scalar_t__ sched_stopped ; 
 int /*<<< orphan*/  tracer_enabled ; 
 int /*<<< orphan*/  tracing_record_cmdline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracing_sched_wakeup_trace (TYPE_1__*,struct task_struct*,int /*<<< orphan*/ ,unsigned long,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
probe_sched_wakeup(struct rq *__rq, struct task_struct *wakee, int success)
{
	struct trace_array_cpu *data;
	unsigned long flags;
	int cpu, pc;

	if (unlikely(!sched_ref))
		return;

	tracing_record_cmdline(current);

	if (!tracer_enabled || sched_stopped)
		return;

	pc = preempt_count();
	local_irq_save(flags);
	cpu = raw_smp_processor_id();
	data = ctx_trace->data[cpu];

	if (likely(!atomic_read(&data->disabled)))
		tracing_sched_wakeup_trace(ctx_trace, wakee, current,
					   flags, pc);

	local_irq_restore(flags);
}