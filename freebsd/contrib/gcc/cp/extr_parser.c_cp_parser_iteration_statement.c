#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum rid { ____Placeholder_rid } rid ;
struct TYPE_14__ {int keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_15__ {unsigned char in_statement; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_KEYWORD ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 void* IN_ITERATION_STMT ; 
 int /*<<< orphan*/  NULL_TREE ; 
#define  RID_DO 130 
#define  RID_FOR 129 
#define  RID_WHILE 128 
 int /*<<< orphan*/  begin_do_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  begin_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  begin_while_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_already_scoped_statement (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_attributes_opt (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_condition (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  cp_parser_expression (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cp_parser_for_init_statement (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_implicitly_scoped_statement (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* cp_parser_require (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (TYPE_2__*,int const,char*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  finish_do_body (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_do_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_for_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_for_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_for_init_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_while_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_while_stmt_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
cp_parser_iteration_statement (cp_parser* parser)
{
  cp_token *token;
  enum rid keyword;
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  tree statement, attributes;
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
  unsigned char in_statement;

/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  /* Get the keyword at the start of the loop.  */
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
  token = cp_parser_require (parser, CPP_KEYWORD, "iteration-statement");
  if (!token)
    return error_mark_node;

  /* Remember whether or not we are already within an iteration
     statement.  */
  in_statement = parser->in_statement;

/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  /* Parse the attributes, if any.  */
  attributes = cp_parser_attributes_opt (parser);

/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
  /* See what kind of keyword it is.  */
  keyword = token->keyword;
  switch (keyword)
    {
    case RID_WHILE:
      {
	tree condition;

	/* Begin the while-statement.  */
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
	statement = begin_while_stmt (attributes);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
	/* Look for the `('.  */
	cp_parser_require (parser, CPP_OPEN_PAREN, "`('");
	/* Parse the condition.  */
	condition = cp_parser_condition (parser);
	finish_while_stmt_cond (condition, statement);
	/* Look for the `)'.  */
	cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'");
	/* Parse the dependent statement.  */
	parser->in_statement = IN_ITERATION_STMT;
	cp_parser_already_scoped_statement (parser);
	parser->in_statement = in_statement;
	/* We're done with the while-statement.  */
	finish_while_stmt (statement);
      }
      break;

    case RID_DO:
      {
	tree expression;

	/* Begin the do-statement.  */
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
	statement = begin_do_stmt (attributes);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
	/* Parse the body of the do-statement.  */
	parser->in_statement = IN_ITERATION_STMT;
	cp_parser_implicitly_scoped_statement (parser, NULL);
	parser->in_statement = in_statement;
	finish_do_body (statement);
	/* Look for the `while' keyword.  */
	cp_parser_require_keyword (parser, RID_WHILE, "`while'");
	/* Look for the `('.  */
	cp_parser_require (parser, CPP_OPEN_PAREN, "`('");
	/* Parse the expression.  */
	expression = cp_parser_expression (parser, /*cast_p=*/false);
	/* We're done with the do-statement.  */
	finish_do_stmt (expression, statement);
	/* Look for the `)'.  */
	cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'");
	/* Look for the `;'.  */
	cp_parser_require (parser, CPP_SEMICOLON, "`;'");
      }
      break;

    case RID_FOR:
      {
	tree condition = NULL_TREE;
	tree expression = NULL_TREE;

	/* Begin the for-statement.  */
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
	statement = begin_for_stmt (attributes);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
	/* Look for the `('.  */
	cp_parser_require (parser, CPP_OPEN_PAREN, "`('");
	/* Parse the initialization.  */
	cp_parser_for_init_statement (parser);
	finish_for_init_stmt (statement);

	/* If there's a condition, process it.  */
	if (cp_lexer_next_token_is_not (parser->lexer, CPP_SEMICOLON))
	  condition = cp_parser_condition (parser);
	finish_for_cond (condition, statement);
	/* Look for the `;'.  */
	cp_parser_require (parser, CPP_SEMICOLON, "`;'");

	/* If there's an expression, process it.  */
	if (cp_lexer_next_token_is_not (parser->lexer, CPP_CLOSE_PAREN))
	  expression = cp_parser_expression (parser, /*cast_p=*/false);
	finish_for_expr (expression, statement);
	/* Look for the `)'.  */
	cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'");

	/* Parse the body of the for-statement.  */
	parser->in_statement = IN_ITERATION_STMT;
	cp_parser_already_scoped_statement (parser);
	parser->in_statement = in_statement;

	/* We're done with the for-statement.  */
	finish_for_stmt (statement);
      }
      break;

    default:
      cp_parser_error (parser, "expected iteration-statement");
      statement = error_mark_node;
      break;
    }

  return statement;
}