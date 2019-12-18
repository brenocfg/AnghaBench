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
struct trace_event {int (* binary ) (struct trace_iterator*,int /*<<< orphan*/ ) ;} ;
struct trace_entry {int /*<<< orphan*/  type; int /*<<< orphan*/  pid; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_PUT_FIELD_RET (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int TRACE_ITER_CONTEXT_INFO ; 
 int TRACE_TYPE_HANDLED ; 
 struct trace_event* ftrace_find_event (int /*<<< orphan*/ ) ; 
 int stub1 (struct trace_iterator*,int /*<<< orphan*/ ) ; 
 int trace_flags ; 

__attribute__((used)) static enum print_line_t print_bin_fmt(struct trace_iterator *iter)
{
	struct trace_seq *s = &iter->seq;
	struct trace_entry *entry;
	struct trace_event *event;

	entry = iter->ent;

	if (trace_flags & TRACE_ITER_CONTEXT_INFO) {
		SEQ_PUT_FIELD_RET(s, entry->pid);
		SEQ_PUT_FIELD_RET(s, iter->cpu);
		SEQ_PUT_FIELD_RET(s, iter->ts);
	}

	event = ftrace_find_event(entry->type);
	return event ? event->binary(iter, 0) : TRACE_TYPE_HANDLED;
}