#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build_x_compound_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_assignment_expression (TYPE_1__*,int) ; 
 scalar_t__ cp_parser_non_integral_constant_expression (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  error_mark_node ; 

__attribute__((used)) static tree
cp_parser_expression (cp_parser* parser, bool cast_p)
{
  tree expression = NULL_TREE;

  while (true)
    {
      tree assignment_expression;

      /* Parse the next assignment-expression.  */
      assignment_expression
	= cp_parser_assignment_expression (parser, cast_p);
      /* If this is the first assignment-expression, we can just
	 save it away.  */
      if (!expression)
	expression = assignment_expression;
      else
	expression = build_x_compound_expr (expression,
					    assignment_expression);
      /* If the next token is not a comma, then we are done with the
	 expression.  */
      if (cp_lexer_next_token_is_not (parser->lexer, CPP_COMMA))
	break;
      /* Consume the `,'.  */
      cp_lexer_consume_token (parser->lexer);
      /* A comma operator cannot appear in a constant-expression.  */
      if (cp_parser_non_integral_constant_expression (parser,
						      "a comma operator"))
	expression = error_mark_node;
    }

  return expression;
}