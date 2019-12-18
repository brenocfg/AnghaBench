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
struct filter_parse_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FILT_ERR_INVALID_OP ; 
 int /*<<< orphan*/  FILT_ERR_OPERAND_TOO_LONG ; 
 int /*<<< orphan*/  FILT_ERR_UNBALANCED_PAREN ; 
 int OP_NONE ; 
 int OP_OPEN_PAREN ; 
 scalar_t__ append_operand_char (struct filter_parse_state*,char) ; 
 int /*<<< orphan*/  clear_operand_string (struct filter_parse_state*) ; 
 int /*<<< orphan*/  curr_operand (struct filter_parse_state*) ; 
 int /*<<< orphan*/  filter_opstack_empty (struct filter_parse_state*) ; 
 int filter_opstack_pop (struct filter_parse_state*) ; 
 int /*<<< orphan*/  filter_opstack_push (struct filter_parse_state*,int) ; 
 int filter_opstack_top (struct filter_parse_state*) ; 
 int infix_get_op (struct filter_parse_state*,char) ; 
 char infix_next (struct filter_parse_state*) ; 
 scalar_t__ is_op_char (struct filter_parse_state*,char) ; 
 int /*<<< orphan*/  is_precedence_lower (struct filter_parse_state*,int,int) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  parse_error (struct filter_parse_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  postfix_append_op (struct filter_parse_state*,int) ; 
 int /*<<< orphan*/  postfix_append_operand (struct filter_parse_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_parse(struct filter_parse_state *ps)
{
	int in_string = 0;
	int op, top_op;
	char ch;

	while ((ch = infix_next(ps))) {
		if (ch == '"') {
			in_string ^= 1;
			continue;
		}

		if (in_string)
			goto parse_operand;

		if (isspace(ch))
			continue;

		if (is_op_char(ps, ch)) {
			op = infix_get_op(ps, ch);
			if (op == OP_NONE) {
				parse_error(ps, FILT_ERR_INVALID_OP, 0);
				return -EINVAL;
			}

			if (strlen(curr_operand(ps))) {
				postfix_append_operand(ps, curr_operand(ps));
				clear_operand_string(ps);
			}

			while (!filter_opstack_empty(ps)) {
				top_op = filter_opstack_top(ps);
				if (!is_precedence_lower(ps, top_op, op)) {
					top_op = filter_opstack_pop(ps);
					postfix_append_op(ps, top_op);
					continue;
				}
				break;
			}

			filter_opstack_push(ps, op);
			continue;
		}

		if (ch == '(') {
			filter_opstack_push(ps, OP_OPEN_PAREN);
			continue;
		}

		if (ch == ')') {
			if (strlen(curr_operand(ps))) {
				postfix_append_operand(ps, curr_operand(ps));
				clear_operand_string(ps);
			}

			top_op = filter_opstack_pop(ps);
			while (top_op != OP_NONE) {
				if (top_op == OP_OPEN_PAREN)
					break;
				postfix_append_op(ps, top_op);
				top_op = filter_opstack_pop(ps);
			}
			if (top_op == OP_NONE) {
				parse_error(ps, FILT_ERR_UNBALANCED_PAREN, 0);
				return -EINVAL;
			}
			continue;
		}
parse_operand:
		if (append_operand_char(ps, ch)) {
			parse_error(ps, FILT_ERR_OPERAND_TOO_LONG, 0);
			return -EINVAL;
		}
	}

	if (strlen(curr_operand(ps)))
		postfix_append_operand(ps, curr_operand(ps));

	while (!filter_opstack_empty(ps)) {
		top_op = filter_opstack_pop(ps);
		if (top_op == OP_NONE)
			break;
		if (top_op == OP_OPEN_PAREN) {
			parse_error(ps, FILT_ERR_UNBALANCED_PAREN, 0);
			return -EINVAL;
		}
		postfix_append_op(ps, top_op);
	}

	return 0;
}