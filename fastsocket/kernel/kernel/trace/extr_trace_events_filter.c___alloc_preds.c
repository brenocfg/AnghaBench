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
struct filter_pred {int /*<<< orphan*/  fn; } ;
struct event_filter {struct filter_pred** preds; scalar_t__ n_preds; } ;
typedef  int /*<<< orphan*/  pred ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct event_filter* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_FILTER_PRED ; 
 int /*<<< orphan*/  __free_preds (struct event_filter*) ; 
 int /*<<< orphan*/  filter_pred_none ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct event_filter *__alloc_preds(void)
{
	struct event_filter *filter;
	struct filter_pred *pred;
	int i;

	filter = kzalloc(sizeof(*filter), GFP_KERNEL);
	if (!filter)
		return ERR_PTR(-ENOMEM);

	filter->n_preds = 0;

	filter->preds = kzalloc(MAX_FILTER_PRED * sizeof(pred), GFP_KERNEL);
	if (!filter->preds)
		goto oom;

	for (i = 0; i < MAX_FILTER_PRED; i++) {
		pred = kzalloc(sizeof(*pred), GFP_KERNEL);
		if (!pred)
			goto oom;
		pred->fn = filter_pred_none;
		filter->preds[i] = pred;
	}

	return filter;

oom:
	__free_preds(filter);
	return ERR_PTR(-ENOMEM);
}