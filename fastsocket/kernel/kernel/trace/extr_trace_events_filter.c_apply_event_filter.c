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
struct ftrace_event_call {int /*<<< orphan*/  flags; int /*<<< orphan*/  filter; } ;
struct filter_parse_state {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TRACE_EVENT_FL_FILTERED ; 
 int /*<<< orphan*/  append_filter_err (struct filter_parse_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  filter_disable_preds (struct ftrace_event_call*) ; 
 int /*<<< orphan*/  filter_ops ; 
 int /*<<< orphan*/  filter_opstack_clear (struct filter_parse_state*) ; 
 int filter_parse (struct filter_parse_state*) ; 
 int init_preds (struct ftrace_event_call*) ; 
 int /*<<< orphan*/  kfree (struct filter_parse_state*) ; 
 struct filter_parse_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_init (struct filter_parse_state*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  postfix_clear (struct filter_parse_state*) ; 
 int /*<<< orphan*/  remove_filter_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_filter_string (int /*<<< orphan*/ ,char*) ; 
 int replace_preds (struct ftrace_event_call*,int /*<<< orphan*/ ,struct filter_parse_state*,char*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strstrip (char*) ; 

int apply_event_filter(struct ftrace_event_call *call, char *filter_string)
{
	int err;
	struct filter_parse_state *ps;

	mutex_lock(&event_mutex);

	err = init_preds(call);
	if (err)
		goto out_unlock;

	if (!strcmp(strstrip(filter_string), "0")) {
		filter_disable_preds(call);
		remove_filter_string(call->filter);
		goto out_unlock;
	}

	err = -ENOMEM;
	ps = kzalloc(sizeof(*ps), GFP_KERNEL);
	if (!ps)
		goto out_unlock;

	filter_disable_preds(call);
	replace_filter_string(call->filter, filter_string);

	parse_init(ps, filter_ops, filter_string);
	err = filter_parse(ps);
	if (err) {
		append_filter_err(ps, call->filter);
		goto out;
	}

	err = replace_preds(call, call->filter, ps, filter_string, false);
	if (err)
		append_filter_err(ps, call->filter);
	else
		call->flags |= TRACE_EVENT_FL_FILTERED;
out:
	filter_opstack_clear(ps);
	postfix_clear(ps);
	kfree(ps);
out_unlock:
	mutex_unlock(&event_mutex);

	return err;
}