#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_SWITCH ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ c_begin_compound_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ c_break_label ; 
 int /*<<< orphan*/  c_end_compound_stmt (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_finish_case (scalar_t__) ; 
 scalar_t__ c_parser_c99_block_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 TYPE_1__ c_parser_expression (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_start_case (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
c_parser_switch_statement (c_parser *parser)
{
  tree block, expr, body, save_break;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  if (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      expr = c_parser_expression (parser).value;
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
    }
  else
    expr = error_mark_node;
  c_start_case (expr);
  save_break = c_break_label;
  c_break_label = NULL_TREE;
  body = c_parser_c99_block_statement (parser);
  c_finish_case (body);
  if (c_break_label)
    add_stmt (build1 (LABEL_EXPR, void_type_node, c_break_label));
  c_break_label = save_break;
  add_stmt (c_end_compound_stmt (block, flag_isoc99));
}