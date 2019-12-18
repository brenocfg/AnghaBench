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
struct c_expr {int /*<<< orphan*/  original_code; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  build_compound_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_expr_no_commas (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct c_expr default_function_array_conversion (struct c_expr) ; 

__attribute__((used)) static struct c_expr
c_parser_expression (c_parser *parser)
{
  struct c_expr expr;
  expr = c_parser_expr_no_commas (parser, NULL);
  while (c_parser_next_token_is (parser, CPP_COMMA))
    {
      struct c_expr next;
      c_parser_consume_token (parser);
      next = c_parser_expr_no_commas (parser, NULL);
      next = default_function_array_conversion (next);
      expr.value = build_compound_expr (expr.value, next.value);
      expr.original_code = COMPOUND_EXPR;
    }
  return expr;
}