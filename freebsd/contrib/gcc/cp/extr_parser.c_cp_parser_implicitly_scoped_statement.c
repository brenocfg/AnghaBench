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
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  begin_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_empty_stmt () ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_compound_statement (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cp_parser_statement (TYPE_1__*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  finish_compound_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
cp_parser_implicitly_scoped_statement (cp_parser* parser, bool *if_p)
{
  tree statement;

  if (if_p != NULL)
    *if_p = false;

  /* Mark if () ; with a special NOP_EXPR.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_SEMICOLON))
    {
      cp_lexer_consume_token (parser->lexer);
      statement = add_stmt (build_empty_stmt ());
    }
  /* if a compound is opened, we simply parse the statement directly.  */
  else if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE))
    /* APPLE LOCAL radar 5982990 */
    statement = cp_parser_compound_statement (parser, NULL, false, false);
  /* If the token is not a `{', then we must take special action.  */
  else
    {
      /* Create a compound-statement.  */
      statement = begin_compound_stmt (0);
      /* Parse the dependent-statement.  */
      cp_parser_statement (parser, NULL_TREE, false, if_p);
      /* Finish the dummy compound-statement.  */
      finish_compound_stmt (statement);
    }

  /* Return the statement.  */
  return statement;
}