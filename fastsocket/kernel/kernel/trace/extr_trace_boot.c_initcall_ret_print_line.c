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
typedef  scalar_t__ u64 ;
struct trace_seq {int dummy; } ;
struct trace_iterator {scalar_t__ ts; struct trace_seq seq; struct trace_entry* ent; } ;
struct trace_entry {int dummy; } ;
struct boot_trace_ret {int /*<<< orphan*/  duration; int /*<<< orphan*/  result; int /*<<< orphan*/  func; } ;
struct trace_boot_ret {struct boot_trace_ret boot_ret; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 unsigned long do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_assign_type (struct trace_boot_ret*,struct trace_entry*) ; 
 int trace_seq_printf (struct trace_seq*,char*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum print_line_t
initcall_ret_print_line(struct trace_iterator *iter)
{
	struct trace_entry *entry = iter->ent;
	struct trace_seq *s = &iter->seq;
	struct trace_boot_ret *field;
	struct boot_trace_ret *init_ret;
	u64 ts;
	unsigned long nsec_rem;
	int ret;

	trace_assign_type(field, entry);
	init_ret = &field->boot_ret;
	ts = iter->ts;
	nsec_rem = do_div(ts, NSEC_PER_SEC);

	ret = trace_seq_printf(s, "[%5ld.%09ld] initcall %s "
			"returned %d after %llu msecs\n",
			(unsigned long) ts,
			nsec_rem,
			init_ret->func, init_ret->result, init_ret->duration);

	if (!ret)
		return TRACE_TYPE_PARTIAL_LINE;
	else
		return TRACE_TYPE_HANDLED;
}