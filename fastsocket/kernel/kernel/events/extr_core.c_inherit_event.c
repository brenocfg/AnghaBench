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
typedef  void* u64 ;
struct task_struct {int dummy; } ;
struct perf_event_context {int /*<<< orphan*/  parent_ctx; int /*<<< orphan*/  lock; } ;
struct hw_perf_event {int /*<<< orphan*/  period_left; void* last_period; void* sample_period; } ;
struct TYPE_2__ {scalar_t__ freq; } ;
struct perf_event {scalar_t__ state; int /*<<< orphan*/  child_mutex; int /*<<< orphan*/  child_list; struct perf_event_context* ctx; int /*<<< orphan*/  overflow_handler_context; int /*<<< orphan*/  overflow_handler; struct hw_perf_event hw; TYPE_1__ attr; int /*<<< orphan*/  refcount; int /*<<< orphan*/  cpu; struct perf_event* parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_event*) ; 
 scalar_t__ PERF_EVENT_STATE_INACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_event_to_ctx (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  atomic_long_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_event (struct perf_event*) ; 
 int /*<<< orphan*/  get_ctx (struct perf_event_context*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event__header_size (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event__id_header_size (struct perf_event*) ; 
 struct perf_event* perf_event_alloc (TYPE_1__*,int /*<<< orphan*/ ,struct task_struct*,struct perf_event*,struct perf_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct perf_event *
inherit_event(struct perf_event *parent_event,
	      struct task_struct *parent,
	      struct perf_event_context *parent_ctx,
	      struct task_struct *child,
	      struct perf_event *group_leader,
	      struct perf_event_context *child_ctx)
{
	struct perf_event *child_event;
	unsigned long flags;

	/*
	 * Instead of creating recursive hierarchies of events,
	 * we link inherited events back to the original parent,
	 * which has a filp for sure, which we use as the reference
	 * count:
	 */
	if (parent_event->parent)
		parent_event = parent_event->parent;

	child_event = perf_event_alloc(&parent_event->attr,
					   parent_event->cpu,
					   child,
					   group_leader, parent_event,
				           NULL, NULL);
	if (IS_ERR(child_event))
		return child_event;

	if (!atomic_long_inc_not_zero(&parent_event->refcount)) {
		free_event(child_event);
		return NULL;
	}

	get_ctx(child_ctx);

	/*
	 * Make the child state follow the state of the parent event,
	 * not its attr.disabled bit.  We hold the parent's mutex,
	 * so we won't race with perf_event_{en, dis}able_family.
	 */
	if (parent_event->state >= PERF_EVENT_STATE_INACTIVE)
		child_event->state = PERF_EVENT_STATE_INACTIVE;
	else
		child_event->state = PERF_EVENT_STATE_OFF;

	if (parent_event->attr.freq) {
		u64 sample_period = parent_event->hw.sample_period;
		struct hw_perf_event *hwc = &child_event->hw;

		hwc->sample_period = sample_period;
		hwc->last_period   = sample_period;

		local64_set(&hwc->period_left, sample_period);
	}

	child_event->ctx = child_ctx;
	child_event->overflow_handler = parent_event->overflow_handler;
	child_event->overflow_handler_context
		= parent_event->overflow_handler_context;

	/*
	 * Precalculate sample_data sizes
	 */
	perf_event__header_size(child_event);
	perf_event__id_header_size(child_event);

	/*
	 * Link it up in the child's context:
	 */
	spin_lock_irqsave(&child_ctx->lock, flags);
	add_event_to_ctx(child_event, child_ctx);
	spin_unlock_irqrestore(&child_ctx->lock, flags);

	/*
	 * Link this into the parent event's child list
	 */
	WARN_ON_ONCE(parent_event->ctx->parent_ctx);
	mutex_lock(&parent_event->child_mutex);
	list_add_tail(&child_event->child_list, &parent_event->child_list);
	mutex_unlock(&parent_event->child_mutex);

	return child_event;
}