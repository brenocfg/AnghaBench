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
struct ftrace_event_call {int /*<<< orphan*/  flags; struct event_filter* filter; } ;
struct event_filter {TYPE_1__** preds; scalar_t__ n_preds; } ;
struct TYPE_2__ {int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 int MAX_FILTER_PRED ; 
 int /*<<< orphan*/  TRACE_EVENT_FL_FILTERED ; 
 int /*<<< orphan*/  filter_pred_none ; 

__attribute__((used)) static void filter_disable_preds(struct ftrace_event_call *call)
{
	struct event_filter *filter = call->filter;
	int i;

	call->flags &= ~TRACE_EVENT_FL_FILTERED;
	filter->n_preds = 0;

	for (i = 0; i < MAX_FILTER_PRED; i++)
		filter->preds[i]->fn = filter_pred_none;
}