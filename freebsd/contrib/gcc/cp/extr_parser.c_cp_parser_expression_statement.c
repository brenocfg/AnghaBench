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
typedef  scalar_t__ tree ;
struct TYPE_5__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_consume_semicolon_at_end_of_statement (TYPE_1__*) ; 
 scalar_t__ cp_parser_expression (TYPE_1__*,int) ; 
 scalar_t__ finish_expr_stmt (scalar_t__) ; 
 int /*<<< orphan*/  finish_stmt () ; 
 scalar_t__ finish_stmt_expr_expr (scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
cp_parser_expression_statement (cp_parser* parser, tree in_statement_expr)
{
  tree statement = NULL_TREE;

  /* If the next token is a ';', then there is no expression
     statement.  */
  if (cp_lexer_next_token_is_not (parser->lexer, CPP_SEMICOLON))
    statement = cp_parser_expression (parser, /*cast_p=*/false);

  /* Consume the final `;'.  */
  cp_parser_consume_semicolon_at_end_of_statement (parser);

  if (in_statement_expr
      && cp_lexer_next_token_is (parser->lexer, CPP_CLOSE_BRACE))
    /* This is the final expression statement of a statement
       expression.  */
    statement = finish_stmt_expr_expr (statement, in_statement_expr);
  else if (statement)
    statement = finish_expr_stmt (statement);
  else
    finish_stmt ();

  return statement;
}