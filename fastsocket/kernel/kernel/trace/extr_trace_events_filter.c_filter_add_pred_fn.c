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
struct ftrace_event_call {int dummy; } ;
struct filter_pred {int dummy; } ;
struct filter_parse_state {int dummy; } ;
struct event_filter {int n_preds; int /*<<< orphan*/ * preds; } ;
typedef  int /*<<< orphan*/  filter_pred_fn_t ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  FILT_ERR_TOO_MANY_PREDS ; 
 int MAX_FILTER_PRED ; 
 int /*<<< orphan*/  filter_clear_pred (int /*<<< orphan*/ ) ; 
 int filter_set_pred (int /*<<< orphan*/ ,struct filter_pred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_error (struct filter_parse_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_add_pred_fn(struct filter_parse_state *ps,
			      struct ftrace_event_call *call,
			      struct event_filter *filter,
			      struct filter_pred *pred,
			      filter_pred_fn_t fn)
{
	int idx, err;

	if (filter->n_preds == MAX_FILTER_PRED) {
		parse_error(ps, FILT_ERR_TOO_MANY_PREDS, 0);
		return -ENOSPC;
	}

	idx = filter->n_preds;
	filter_clear_pred(filter->preds[idx]);
	err = filter_set_pred(filter->preds[idx], pred, fn);
	if (err)
		return err;

	filter->n_preds++;

	return 0;
}