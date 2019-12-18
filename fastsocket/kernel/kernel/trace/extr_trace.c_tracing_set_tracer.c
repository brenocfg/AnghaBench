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
struct tracer {scalar_t__ init; scalar_t__ use_max_tr; int /*<<< orphan*/  (* reset ) (struct trace_array*) ;int /*<<< orphan*/  name; struct tracer* next; } ;
struct trace_option_dentry {int dummy; } ;
struct trace_array {int entries; } ;
struct TYPE_2__ {int entries; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int EINVAL ; 
 struct trace_option_dentry* create_trace_option_files (struct tracer*) ; 
 struct tracer* current_trace ; 
 int /*<<< orphan*/  destroy_trace_option_files (struct trace_option_dentry*) ; 
 struct trace_array global_trace ; 
 TYPE_1__ max_tr ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_expanded ; 
 int ring_buffer_resize (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (struct trace_array*) ; 
 int /*<<< orphan*/  trace_branch_disable () ; 
 int /*<<< orphan*/  trace_branch_enable (struct trace_array*) ; 
 int /*<<< orphan*/  trace_buf_size ; 
 struct tracer* trace_types ; 
 int /*<<< orphan*/  trace_types_lock ; 
 int tracer_init (struct tracer*,struct trace_array*) ; 
 int tracing_resize_ring_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tracing_set_tracer(const char *buf)
{
	static struct trace_option_dentry *topts;
	struct trace_array *tr = &global_trace;
	struct tracer *t;
	int ret = 0;

	mutex_lock(&trace_types_lock);

	if (!ring_buffer_expanded) {
		ret = tracing_resize_ring_buffer(trace_buf_size);
		if (ret < 0)
			goto out;
		ret = 0;
	}

	for (t = trace_types; t; t = t->next) {
		if (strcmp(t->name, buf) == 0)
			break;
	}
	if (!t) {
		ret = -EINVAL;
		goto out;
	}
	if (t == current_trace)
		goto out;

	trace_branch_disable();
	if (current_trace && current_trace->reset)
		current_trace->reset(tr);
	if (current_trace && current_trace->use_max_tr) {
		/*
		 * We don't free the ring buffer. instead, resize it because
		 * The max_tr ring buffer has some state (e.g. ring->clock) and
		 * we want preserve it.
		 */
		ring_buffer_resize(max_tr.buffer, 1);
		max_tr.entries = 1;
	}
	destroy_trace_option_files(topts);

	current_trace = t;

	topts = create_trace_option_files(current_trace);
	if (current_trace->use_max_tr) {
		ret = ring_buffer_resize(max_tr.buffer, global_trace.entries);
		if (ret < 0)
			goto out;
		max_tr.entries = global_trace.entries;
	}

	if (t->init) {
		ret = tracer_init(t, tr);
		if (ret)
			goto out;
	}

	trace_branch_enable(tr);
 out:
	mutex_unlock(&trace_types_lock);

	return ret;
}