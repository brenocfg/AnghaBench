#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum rid { ____Placeholder_rid } rid ;
struct TYPE_11__ {int keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_12__ {int in_switch_statement_p; unsigned char in_statement; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_KEYWORD ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  EXPR_LOCUS (int /*<<< orphan*/ ) ; 
 unsigned char IN_SWITCH_STMT ; 
 int /*<<< orphan*/  OPT_Wparentheses ; 
 int /*<<< orphan*/  RID_ELSE ; 
#define  RID_IF 129 
#define  RID_SWITCH 128 
 int /*<<< orphan*/  begin_else_clause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  begin_if_stmt () ; 
 int /*<<< orphan*/  begin_switch_stmt () ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_next_token_is_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_condition (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  cp_parser_implicitly_scoped_statement (TYPE_2__*,int*) ; 
 TYPE_1__* cp_parser_require (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_closing_parenthesis (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  cp_parser_skip_to_end_of_statement (TYPE_2__*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  finish_else_clause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_if_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_if_stmt_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_switch_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_switch_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_then_clause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
cp_parser_selection_statement (cp_parser* parser, bool *if_p)
{
  cp_token *token;
  enum rid keyword;

  if (if_p != NULL)
    *if_p = false;

  /* Peek at the next token.  */
  token = cp_parser_require (parser, CPP_KEYWORD, "selection-statement");

  /* See what kind of keyword it is.  */
  keyword = token->keyword;
  switch (keyword)
    {
    case RID_IF:
    case RID_SWITCH:
      {
	tree statement;
	tree condition;

	/* Look for the `('.  */
	if (!cp_parser_require (parser, CPP_OPEN_PAREN, "`('"))
	  {
	    cp_parser_skip_to_end_of_statement (parser);
	    return error_mark_node;
	  }

	/* Begin the selection-statement.  */
	if (keyword == RID_IF)
	  statement = begin_if_stmt ();
	else
	  statement = begin_switch_stmt ();

	/* Parse the condition.  */
	condition = cp_parser_condition (parser);
	/* Look for the `)'.  */
	if (!cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'"))
	  cp_parser_skip_to_closing_parenthesis (parser, true, false,
						 /*consume_paren=*/true);

	if (keyword == RID_IF)
	  {
	    bool nested_if;

	    /* Add the condition.  */
	    finish_if_stmt_cond (condition, statement);

	    /* Parse the then-clause.  */
	    cp_parser_implicitly_scoped_statement (parser, &nested_if);
	    finish_then_clause (statement);

	    /* If the next token is `else', parse the else-clause.  */
	    if (cp_lexer_next_token_is_keyword (parser->lexer,
						RID_ELSE))
	      {
		/* Consume the `else' keyword.  */
		cp_lexer_consume_token (parser->lexer);
		begin_else_clause (statement);
		/* Parse the else-clause.  */
		cp_parser_implicitly_scoped_statement (parser, NULL);
		finish_else_clause (statement);

		/* If we are currently parsing a then-clause, then
		   IF_P will not be NULL.  We set it to true to
		   indicate that this if statement has an else clause.
		   This may trigger the Wparentheses warning below
		   when we get back up to the parent if statement.  */
		if (if_p != NULL)
		  *if_p = true;
	      }
	    else
	      {
		/* This if statement does not have an else clause.  If
		   NESTED_IF is true, then the then-clause is an if
		   statement which does have an else clause.  We warn
		   about the potential ambiguity.  */
		if (nested_if)
		  warning (OPT_Wparentheses,
			   ("%Hsuggest explicit braces "
			    "to avoid ambiguous %<else%>"),
			   EXPR_LOCUS (statement));
	      }

	    /* Now we're all done with the if-statement.  */
	    finish_if_stmt (statement);
	  }
	else
	  {
	    bool in_switch_statement_p;
	    unsigned char in_statement;

	    /* Add the condition.  */
	    finish_switch_cond (condition, statement);

	    /* Parse the body of the switch-statement.  */
	    in_switch_statement_p = parser->in_switch_statement_p;
	    in_statement = parser->in_statement;
	    parser->in_switch_statement_p = true;
	    parser->in_statement |= IN_SWITCH_STMT;
	    cp_parser_implicitly_scoped_statement (parser, NULL);
	    parser->in_switch_statement_p = in_switch_statement_p;
	    parser->in_statement = in_statement;

	    /* Now we're all done with the switch-statement.  */
	    finish_switch_stmt (statement);
	  }

	return statement;
      }
      break;

    default:
      cp_parser_error (parser, "expected selection-statement");
      return error_mark_node;
    }
}