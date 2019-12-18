#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  enum rid { ____Placeholder_rid } rid ;
struct TYPE_19__ {scalar_t__ type; int keyword; int /*<<< orphan*/  location; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_20__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 scalar_t__ CPP_COLON ; 
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_KEYWORD ; 
 scalar_t__ CPP_NAME ; 
 scalar_t__ CPP_OPEN_BRACE ; 
 scalar_t__ CPP_PRAGMA ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 scalar_t__ NULL_TREE ; 
#define  RID_AT_CATCH 144 
#define  RID_AT_FINALLY 143 
#define  RID_AT_SYNCHRONIZED 142 
#define  RID_AT_THROW 141 
#define  RID_AT_TRY 140 
#define  RID_BREAK 139 
#define  RID_CASE 138 
#define  RID_CONTINUE 137 
#define  RID_DEFAULT 136 
#define  RID_DO 135 
#define  RID_FOR 134 
#define  RID_GOTO 133 
#define  RID_IF 132 
#define  RID_RETURN 131 
#define  RID_SWITCH 130 
#define  RID_TRY 129 
#define  RID_WHILE 128 
 int /*<<< orphan*/  SET_EXPR_LOCATION (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ STATEMENT_CODE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CODE (scalar_t__) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_compound_statement (TYPE_2__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cp_parser_declaration_statement (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 scalar_t__ cp_parser_expression_statement (TYPE_2__*,scalar_t__) ; 
 scalar_t__ cp_parser_iteration_statement (TYPE_2__*) ; 
 scalar_t__ cp_parser_jump_statement (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_label_for_labeled_statement (TYPE_2__*) ; 
 scalar_t__ cp_parser_objc_statement (TYPE_2__*) ; 
 scalar_t__ cp_parser_parse_definitely (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_pragma (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_selection_statement (TYPE_2__*,int*) ; 
 scalar_t__ cp_parser_try_block (TYPE_2__*) ; 
 int /*<<< orphan*/  pragma_compound ; 
 int /*<<< orphan*/  pragma_stmt ; 

__attribute__((used)) static void
cp_parser_statement (cp_parser* parser, tree in_statement_expr,
		     bool in_compound, bool *if_p)
{
  tree statement;
  cp_token *token;
  location_t statement_location;

 restart:
  if (if_p != NULL)
    *if_p = false;
  /* There is no statement yet.  */
  statement = NULL_TREE;
  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);
  /* Remember the location of the first token in the statement.  */
  statement_location = token->location;
  /* If this is a keyword, then that will often determine what kind of
     statement we have.  */
  if (token->type == CPP_KEYWORD)
    {
      enum rid keyword = token->keyword;

      switch (keyword)
	{
	case RID_CASE:
	case RID_DEFAULT:
	  /* Looks like a labeled-statement with a case label.
	     Parse the label, and then use tail recursion to parse
	     the statement.  */
	  cp_parser_label_for_labeled_statement (parser);
	  goto restart;

	case RID_IF:
	case RID_SWITCH:
	  statement = cp_parser_selection_statement (parser, if_p);
	  break;

	case RID_WHILE:
	case RID_DO:
	case RID_FOR:
	  statement = cp_parser_iteration_statement (parser);
	  break;

	case RID_BREAK:
	case RID_CONTINUE:
	case RID_RETURN:
	case RID_GOTO:
	  statement = cp_parser_jump_statement (parser);
	  break;

	  /* Objective-C++ exception-handling constructs.  */
	case RID_AT_TRY:
	case RID_AT_CATCH:
	case RID_AT_FINALLY:
	case RID_AT_SYNCHRONIZED:
	case RID_AT_THROW:
	  statement = cp_parser_objc_statement (parser);
	  break;

	case RID_TRY:
	  statement = cp_parser_try_block (parser);
	  break;

	default:
	  /* It might be a keyword like `int' that can start a
	     declaration-statement.  */
	  break;
	}
    }
  else if (token->type == CPP_NAME)
    {
      /* If the next token is a `:', then we are looking at a
	 labeled-statement.  */
      token = cp_lexer_peek_nth_token (parser->lexer, 2);
      if (token->type == CPP_COLON)
	{
	  /* Looks like a labeled-statement with an ordinary label.
	     Parse the label, and then use tail recursion to parse
	     the statement.  */
	  cp_parser_label_for_labeled_statement (parser);
	  goto restart;
	}
    }
  /* Anything that starts with a `{' must be a compound-statement.  */
  else if (token->type == CPP_OPEN_BRACE)
    /* APPLE LOCAL radar 5982990 */
    statement = cp_parser_compound_statement (parser, NULL, false, false);
  /* CPP_PRAGMA is a #pragma inside a function body, which constitutes
     a statement all its own.  */
  else if (token->type == CPP_PRAGMA)
    {
      /* Only certain OpenMP pragmas are attached to statements, and thus
	 are considered statements themselves.  All others are not.  In
	 the context of a compound, accept the pragma as a "statement" and
	 return so that we can check for a close brace.  Otherwise we
	 require a real statement and must go back and read one.  */
      if (in_compound)
	cp_parser_pragma (parser, pragma_compound);
      else if (!cp_parser_pragma (parser, pragma_stmt))
	goto restart;
      return;
    }
  else if (token->type == CPP_EOF)
    {
      cp_parser_error (parser, "expected statement");
      return;
    }

  /* Everything else must be a declaration-statement or an
     expression-statement.  Try for the declaration-statement
     first, unless we are looking at a `;', in which case we know that
     we have an expression-statement.  */
  if (!statement)
    {
      if (cp_lexer_next_token_is_not (parser->lexer, CPP_SEMICOLON))
	{
	  cp_parser_parse_tentatively (parser);
	  /* Try to parse the declaration-statement.  */
	  cp_parser_declaration_statement (parser);
	  /* If that worked, we're done.  */
	  if (cp_parser_parse_definitely (parser))
	    return;
	}
      /* Look for an expression-statement instead.  */
      statement = cp_parser_expression_statement (parser, in_statement_expr);
    }

  /* Set the line number for the statement.  */
  if (statement && STATEMENT_CODE_P (TREE_CODE (statement)))
    SET_EXPR_LOCATION (statement, statement_location);
}