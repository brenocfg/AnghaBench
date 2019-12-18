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
struct task_struct {struct perf_event_context** perf_event_ctxp; } ;
struct perf_event_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inherit; } ;
struct perf_event {int /*<<< orphan*/  pmu; TYPE_1__ attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct perf_event_context* alloc_perf_context (int /*<<< orphan*/ ,struct task_struct*) ; 
 int inherit_group (struct perf_event*,struct task_struct*,struct perf_event_context*,struct task_struct*,struct perf_event_context*) ; 

__attribute__((used)) static int
inherit_task_group(struct perf_event *event, struct task_struct *parent,
		   struct perf_event_context *parent_ctx,
		   struct task_struct *child, int ctxn,
		   int *inherited_all)
{
	int ret;
	struct perf_event_context *child_ctx;

	if (!event->attr.inherit) {
		*inherited_all = 0;
		return 0;
	}

	child_ctx = child->perf_event_ctxp[ctxn];
	if (!child_ctx) {
		/*
		 * This is executed from the parent task context, so
		 * inherit events that have been marked for cloning.
		 * First allocate and initialize a context for the
		 * child.
		 */

		child_ctx = alloc_perf_context(event->pmu, child);
		if (!child_ctx)
			return -ENOMEM;

		child->perf_event_ctxp[ctxn] = child_ctx;
	}

	ret = inherit_group(event, parent, parent_ctx,
			    child, child_ctx);

	if (ret)
		*inherited_all = 0;

	return ret;
}