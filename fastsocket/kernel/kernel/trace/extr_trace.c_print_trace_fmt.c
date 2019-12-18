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
struct trace_seq {int dummy; } ;
struct trace_iterator {int iter_flags; struct trace_entry* ent; struct trace_seq seq; } ;
struct trace_event {int (* trace ) (struct trace_iterator*,unsigned long) ;} ;
struct trace_entry {int /*<<< orphan*/  type; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int TRACE_FILE_LAT_FMT ; 
 int TRACE_ITER_CONTEXT_INFO ; 
 int TRACE_ITER_SYM_MASK ; 
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 struct trace_event* ftrace_find_event (int /*<<< orphan*/ ) ; 
 int stub1 (struct trace_iterator*,unsigned long) ; 
 int /*<<< orphan*/  test_cpu_buff_start (struct trace_iterator*) ; 
 int trace_flags ; 
 int /*<<< orphan*/  trace_print_context (struct trace_iterator*) ; 
 int /*<<< orphan*/  trace_print_lat_context (struct trace_iterator*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum print_line_t print_trace_fmt(struct trace_iterator *iter)
{
	struct trace_seq *s = &iter->seq;
	unsigned long sym_flags = (trace_flags & TRACE_ITER_SYM_MASK);
	struct trace_entry *entry;
	struct trace_event *event;

	entry = iter->ent;

	test_cpu_buff_start(iter);

	event = ftrace_find_event(entry->type);

	if (trace_flags & TRACE_ITER_CONTEXT_INFO) {
		if (iter->iter_flags & TRACE_FILE_LAT_FMT) {
			if (!trace_print_lat_context(iter))
				goto partial;
		} else {
			if (!trace_print_context(iter))
				goto partial;
		}
	}

	if (event)
		return event->trace(iter, sym_flags);

	if (!trace_seq_printf(s, "Unknown type %d\n", entry->type))
		goto partial;

	return TRACE_TYPE_HANDLED;
partial:
	return TRACE_TYPE_PARTIAL_LINE;
}