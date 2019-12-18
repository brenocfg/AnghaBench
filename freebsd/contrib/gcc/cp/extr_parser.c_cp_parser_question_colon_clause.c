#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_7__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COLON ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build_x_conditional_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_allow_gnu_extensions_p (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_assignment_expression (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cp_parser_expression (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static tree
cp_parser_question_colon_clause (cp_parser* parser, tree logical_or_expr)
{
  tree expr;
  tree assignment_expr;

  /* Consume the `?' token.  */
  cp_lexer_consume_token (parser->lexer);
  if (cp_parser_allow_gnu_extensions_p (parser)
      && cp_lexer_next_token_is (parser->lexer, CPP_COLON))
    /* Implicit true clause.  */
    expr = NULL_TREE;
  else
    /* Parse the expression.  */
    expr = cp_parser_expression (parser, /*cast_p=*/false);

  /* The next token should be a `:'.  */
  cp_parser_require (parser, CPP_COLON, "`:'");
  /* Parse the assignment-expression.  */
  assignment_expr = cp_parser_assignment_expression (parser, /*cast_p=*/false);

  /* Build the conditional-expression.  */
  return build_x_conditional_expr (logical_or_expr,
				   expr,
				   assignment_expr);
}