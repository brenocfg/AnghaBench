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
struct trace_iterator {int /*<<< orphan*/  ts; int /*<<< orphan*/  cpu; int /*<<< orphan*/  ent; struct trace_seq seq; } ;
struct kmemtrace_user_event {int event_size; unsigned long ptr; int /*<<< orphan*/  call_site; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  cpu; int /*<<< orphan*/  type_id; int /*<<< orphan*/  event_id; } ;
struct kmemtrace_free_entry {scalar_t__ ptr; int /*<<< orphan*/  call_site; int /*<<< orphan*/  type_id; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int /*<<< orphan*/  KMEMTRACE_USER_FREE ; 
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 int /*<<< orphan*/  trace_assign_type (struct kmemtrace_free_entry*,int /*<<< orphan*/ ) ; 
 struct kmemtrace_user_event* trace_seq_reserve (struct trace_seq*,int) ; 

__attribute__((used)) static enum print_line_t
kmemtrace_print_free_user(struct trace_iterator *iter, int flags)
{
	struct trace_seq *s = &iter->seq;
	struct kmemtrace_free_entry *entry;
	struct kmemtrace_user_event *ev;

	trace_assign_type(entry, iter->ent);

	ev = trace_seq_reserve(s, sizeof(*ev));
	if (!ev)
		return TRACE_TYPE_PARTIAL_LINE;

	ev->event_id		= KMEMTRACE_USER_FREE;
	ev->type_id		= entry->type_id;
	ev->event_size		= sizeof(*ev);
	ev->cpu			= iter->cpu;
	ev->timestamp		= iter->ts;
	ev->call_site		= entry->call_site;
	ev->ptr			= (unsigned long)entry->ptr;

	return TRACE_TYPE_HANDLED;
}