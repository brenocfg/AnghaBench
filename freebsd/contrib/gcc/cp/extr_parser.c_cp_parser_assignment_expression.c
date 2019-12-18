#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_8__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_QUERY ; 
 int ERROR_MARK ; 
 int /*<<< orphan*/  RID_THROW ; 
 int /*<<< orphan*/  build_x_modify_expr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cp_parser_assignment_operator_opt (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_binary_expression (TYPE_1__*,int) ; 
 scalar_t__ cp_parser_non_integral_constant_expression (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cp_parser_question_colon_clause (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_throw_expression (TYPE_1__*) ; 
 int /*<<< orphan*/  error_mark_node ; 

__attribute__((used)) static tree
cp_parser_assignment_expression (cp_parser* parser, bool cast_p)
{
  tree expr;

  /* If the next token is the `throw' keyword, then we're looking at
     a throw-expression.  */
  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_THROW))
    expr = cp_parser_throw_expression (parser);
  /* Otherwise, it must be that we are looking at a
     logical-or-expression.  */
  else
    {
      /* Parse the binary expressions (logical-or-expression).  */
      expr = cp_parser_binary_expression (parser, cast_p);
      /* If the next token is a `?' then we're actually looking at a
	 conditional-expression.  */
      if (cp_lexer_next_token_is (parser->lexer, CPP_QUERY))
	return cp_parser_question_colon_clause (parser, expr);
      else
	{
	  enum tree_code assignment_operator;

	  /* If it's an assignment-operator, we're using the second
	     production.  */
	  assignment_operator
	    = cp_parser_assignment_operator_opt (parser);
	  if (assignment_operator != ERROR_MARK)
	    {
	      tree rhs;

	      /* Parse the right-hand side of the assignment.  */
	      rhs = cp_parser_assignment_expression (parser, cast_p);
	      /* An assignment may not appear in a
		 constant-expression.  */
	      if (cp_parser_non_integral_constant_expression (parser,
							      "an assignment"))
		return error_mark_node;
	      /* Build the assignment expression.  */
	      expr = build_x_modify_expr (expr,
					  assignment_operator,
					  rhs);
	    }
	}
    }

  return expr;
}