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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_ELSE ; 
 int /*<<< orphan*/  RID_IF ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_begin_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_end_compound_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_finish_if_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_if_body (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_paren_condition (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 

__attribute__((used)) static void
c_parser_if_statement (c_parser *parser)
{
  tree block;
  location_t loc;
  tree cond;
  bool first_if = false, second_if = false;
  tree first_body, second_body;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_IF));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  first_body = c_parser_if_body (parser, &first_if);
  if (c_parser_next_token_is_keyword (parser, RID_ELSE))
    {
      c_parser_consume_token (parser);
      second_body = c_parser_if_body (parser, &second_if);
    }
  else
    second_body = NULL_TREE;
  c_finish_if_stmt (loc, cond, first_body, second_body, first_if);
  add_stmt (c_end_compound_stmt (block, flag_isoc99));
}