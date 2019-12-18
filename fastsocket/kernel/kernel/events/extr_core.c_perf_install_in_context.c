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
struct task_struct {int dummy; } ;
struct perf_event_context {int /*<<< orphan*/  lock; scalar_t__ is_active; int /*<<< orphan*/  mutex; struct task_struct* task; } ;
struct perf_event {int cpu; struct perf_event_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_install_in_context ; 
 int /*<<< orphan*/  add_event_to_ctx (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  cpu_function_call (int,int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_function_call (struct task_struct*,int /*<<< orphan*/ ,struct perf_event*) ; 

__attribute__((used)) static void
perf_install_in_context(struct perf_event_context *ctx,
			struct perf_event *event,
			int cpu)
{
	struct task_struct *task = ctx->task;

	lockdep_assert_held(&ctx->mutex);

	event->ctx = ctx;
	if (event->cpu != -1)
		event->cpu = cpu;

	if (!task) {
		/*
		 * Per cpu events are installed via an smp call and
		 * the install is always successful.
		 */
		cpu_function_call(cpu, __perf_install_in_context, event);
		return;
	}

retry:
	if (!task_function_call(task, __perf_install_in_context, event))
		return;

	spin_lock_irq(&ctx->lock);
	/*
	 * If we failed to find a running task, but find the context active now
	 * that we've acquired the ctx->lock, retry.
	 */
	if (ctx->is_active) {
		spin_unlock_irq(&ctx->lock);
		goto retry;
	}

	/*
	 * Since the task isn't running, its safe to add the event, us holding
	 * the ctx->lock ensures the task won't get scheduled in.
	 */
	add_event_to_ctx(event, ctx);
	spin_unlock_irq(&ctx->lock);
}