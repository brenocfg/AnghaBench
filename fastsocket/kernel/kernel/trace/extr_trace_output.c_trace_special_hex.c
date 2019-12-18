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
struct special_entry {int /*<<< orphan*/  arg3; int /*<<< orphan*/  arg2; int /*<<< orphan*/  arg1; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_PUT_HEX_FIELD_RET (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int TRACE_TYPE_HANDLED ; 
 int /*<<< orphan*/  trace_assign_type (struct special_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum print_line_t trace_special_hex(struct trace_iterator *iter,
					   int flags)
{
	struct special_entry *field;
	struct trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	SEQ_PUT_HEX_FIELD_RET(s, field->arg1);
	SEQ_PUT_HEX_FIELD_RET(s, field->arg2);
	SEQ_PUT_HEX_FIELD_RET(s, field->arg3);

	return TRACE_TYPE_HANDLED;
}