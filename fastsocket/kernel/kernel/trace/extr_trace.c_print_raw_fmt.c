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
struct trace_iterator {int /*<<< orphan*/  ts; int /*<<< orphan*/  cpu; struct trace_entry* ent; struct trace_seq seq; } ;
struct trace_event {int (* raw ) (struct trace_iterator*,int /*<<< orphan*/ ) ;} ;
struct trace_entry {int /*<<< orphan*/  type; int /*<<< orphan*/  pid; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int TRACE_ITER_CONTEXT_INFO ; 
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 struct trace_event* ftrace_find_event (int /*<<< orphan*/ ) ; 
 int stub1 (struct trace_iterator*,int /*<<< orphan*/ ) ; 
 int trace_flags ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static enum print_line_t print_raw_fmt(struct trace_iterator *iter)
{
	struct trace_seq *s = &iter->seq;
	struct trace_entry *entry;
	struct trace_event *event;

	entry = iter->ent;

	if (trace_flags & TRACE_ITER_CONTEXT_INFO) {
		if (!trace_seq_printf(s, "%d %d %llu ",
				      entry->pid, iter->cpu, iter->ts))
			goto partial;
	}

	event = ftrace_find_event(entry->type);
	if (event)
		return event->raw(iter, 0);

	if (!trace_seq_printf(s, "%d ?\n", entry->type))
		goto partial;

	return TRACE_TYPE_HANDLED;
partial:
	return TRACE_TYPE_PARTIAL_LINE;
}