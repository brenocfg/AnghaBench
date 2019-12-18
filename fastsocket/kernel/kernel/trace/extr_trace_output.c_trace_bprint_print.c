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
struct trace_iterator {struct trace_seq seq; struct trace_entry* ent; } ;
struct trace_entry {int dummy; } ;
struct bprint_entry {int /*<<< orphan*/  buf; int /*<<< orphan*/  fmt; int /*<<< orphan*/  ip; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 int /*<<< orphan*/  seq_print_ip_sym (struct trace_seq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_assign_type (struct bprint_entry*,struct trace_entry*) ; 
 int /*<<< orphan*/  trace_seq_bprintf (struct trace_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static enum print_line_t
trace_bprint_print(struct trace_iterator *iter, int flags)
{
	struct trace_entry *entry = iter->ent;
	struct trace_seq *s = &iter->seq;
	struct bprint_entry *field;

	trace_assign_type(field, entry);

	if (!seq_print_ip_sym(s, field->ip, flags))
		goto partial;

	if (!trace_seq_puts(s, ": "))
		goto partial;

	if (!trace_seq_bprintf(s, field->fmt, field->buf))
		goto partial;

	return TRACE_TYPE_HANDLED;

 partial:
	return TRACE_TYPE_PARTIAL_LINE;
}