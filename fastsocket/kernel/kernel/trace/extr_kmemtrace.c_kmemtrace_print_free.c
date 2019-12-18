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
struct trace_iterator {int /*<<< orphan*/  ent; struct trace_seq seq; } ;
struct kmemtrace_free_entry {scalar_t__ ptr; scalar_t__ call_site; int /*<<< orphan*/  type_id; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 int /*<<< orphan*/  trace_assign_type (struct kmemtrace_free_entry*,int /*<<< orphan*/ ) ; 
 int trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ,void*,unsigned long) ; 

__attribute__((used)) static enum print_line_t
kmemtrace_print_free(struct trace_iterator *iter, int flags)
{
	struct trace_seq *s = &iter->seq;
	struct kmemtrace_free_entry *entry;
	int ret;

	trace_assign_type(entry, iter->ent);

	ret = trace_seq_printf(s, "type_id %d call_site %pF ptr %lu\n",
			       entry->type_id, (void *)entry->call_site,
			       (unsigned long)entry->ptr);

	if (!ret)
		return TRACE_TYPE_PARTIAL_LINE;
	return TRACE_TYPE_HANDLED;
}