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
struct perf_event_context {int /*<<< orphan*/  mutex; int /*<<< orphan*/  generation; int /*<<< orphan*/  parent_ctx; int /*<<< orphan*/  pmu; } ;
struct perf_event_attr {int dummy; } ;
struct perf_event {int /*<<< orphan*/  mutex; int /*<<< orphan*/  generation; int /*<<< orphan*/  parent_ctx; int /*<<< orphan*/  pmu; } ;
typedef  int /*<<< orphan*/  perf_overflow_handler_t ;

/* Variables and functions */
 struct perf_event_context* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct perf_event_context*) ; 
 int PTR_ERR (struct perf_event_context*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 struct perf_event_context* find_get_context (int /*<<< orphan*/ ,struct task_struct*,int) ; 
 int /*<<< orphan*/  free_event (struct perf_event_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct perf_event_context* perf_event_alloc (struct perf_event_attr*,int,struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  perf_install_in_context (struct perf_event_context*,struct perf_event_context*,int) ; 
 int /*<<< orphan*/  perf_unpin_context (struct perf_event_context*) ; 

struct perf_event *
perf_event_create_kernel_counter(struct perf_event_attr *attr, int cpu,
				 struct task_struct *task,
				 perf_overflow_handler_t overflow_handler,
				 void *context)
{
	struct perf_event_context *ctx;
	struct perf_event *event;
	int err;

	/*
	 * Get the target context (task or percpu):
	 */

	event = perf_event_alloc(attr, cpu, task, NULL, NULL,
				 overflow_handler, context);
	if (IS_ERR(event)) {
		err = PTR_ERR(event);
		goto err;
	}

	ctx = find_get_context(event->pmu, task, cpu);
	if (IS_ERR(ctx)) {
		err = PTR_ERR(ctx);
		goto err_free;
	}

	WARN_ON_ONCE(ctx->parent_ctx);
	mutex_lock(&ctx->mutex);
	perf_install_in_context(ctx, event, cpu);
	++ctx->generation;
	perf_unpin_context(ctx);
	mutex_unlock(&ctx->mutex);

	return event;

err_free:
	free_event(event);
err:
	return ERR_PTR(err);
}