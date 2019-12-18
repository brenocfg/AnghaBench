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
struct trace_entry {int preempt_count; int flags; int /*<<< orphan*/  lock_depth; int /*<<< orphan*/  pid; } ;
struct task_struct {int /*<<< orphan*/  lock_depth; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int HARDIRQ_MASK ; 
 int SOFTIRQ_MASK ; 
 int TRACE_FLAG_HARDIRQ ; 
 int TRACE_FLAG_IRQS_NOSUPPORT ; 
 int TRACE_FLAG_IRQS_OFF ; 
 int TRACE_FLAG_NEED_RESCHED ; 
 int TRACE_FLAG_SOFTIRQ ; 
 struct task_struct* current ; 
 scalar_t__ irqs_disabled_flags (unsigned long) ; 
 scalar_t__ need_resched () ; 

void
tracing_generic_entry_update(struct trace_entry *entry, unsigned long flags,
			     int pc)
{
	struct task_struct *tsk = current;

	entry->preempt_count		= pc & 0xff;
	entry->pid			= (tsk) ? tsk->pid : 0;
	entry->lock_depth		= (tsk) ? tsk->lock_depth : 0;
	entry->flags =
#ifdef CONFIG_TRACE_IRQFLAGS_SUPPORT
		(irqs_disabled_flags(flags) ? TRACE_FLAG_IRQS_OFF : 0) |
#else
		TRACE_FLAG_IRQS_NOSUPPORT |
#endif
		((pc & HARDIRQ_MASK) ? TRACE_FLAG_HARDIRQ : 0) |
		((pc & SOFTIRQ_MASK) ? TRACE_FLAG_SOFTIRQ : 0) |
		(need_resched() ? TRACE_FLAG_NEED_RESCHED : 0);
}