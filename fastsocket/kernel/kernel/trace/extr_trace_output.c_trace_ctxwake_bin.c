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
struct ctx_switch_entry {int /*<<< orphan*/  next_state; int /*<<< orphan*/  next_prio; int /*<<< orphan*/  next_pid; int /*<<< orphan*/  prev_state; int /*<<< orphan*/  prev_prio; int /*<<< orphan*/  prev_pid; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_PUT_FIELD_RET (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int TRACE_TYPE_HANDLED ; 
 int /*<<< orphan*/  trace_assign_type (struct ctx_switch_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum print_line_t trace_ctxwake_bin(struct trace_iterator *iter,
					   int flags)
{
	struct ctx_switch_entry *field;
	struct trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	SEQ_PUT_FIELD_RET(s, field->prev_pid);
	SEQ_PUT_FIELD_RET(s, field->prev_prio);
	SEQ_PUT_FIELD_RET(s, field->prev_state);
	SEQ_PUT_FIELD_RET(s, field->next_pid);
	SEQ_PUT_FIELD_RET(s, field->next_prio);
	SEQ_PUT_FIELD_RET(s, field->next_state);

	return TRACE_TYPE_HANDLED;
}