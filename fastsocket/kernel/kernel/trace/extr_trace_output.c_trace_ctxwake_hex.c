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
struct ctx_switch_entry {int prev_pid; int prev_prio; int next_cpu; int next_pid; int next_prio; int /*<<< orphan*/  next_state; int /*<<< orphan*/  prev_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_PUT_HEX_FIELD_RET (struct trace_seq*,int) ; 
 int TRACE_TYPE_HANDLED ; 
 void* task_state_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_assign_type (struct ctx_switch_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trace_ctxwake_hex(struct trace_iterator *iter, char S)
{
	struct ctx_switch_entry *field;
	struct trace_seq *s = &iter->seq;
	int T;

	trace_assign_type(field, iter->ent);

	if (!S)
		S = task_state_char(field->prev_state);
	T = task_state_char(field->next_state);

	SEQ_PUT_HEX_FIELD_RET(s, field->prev_pid);
	SEQ_PUT_HEX_FIELD_RET(s, field->prev_prio);
	SEQ_PUT_HEX_FIELD_RET(s, S);
	SEQ_PUT_HEX_FIELD_RET(s, field->next_cpu);
	SEQ_PUT_HEX_FIELD_RET(s, field->next_pid);
	SEQ_PUT_HEX_FIELD_RET(s, field->next_prio);
	SEQ_PUT_HEX_FIELD_RET(s, T);

	return TRACE_TYPE_HANDLED;
}