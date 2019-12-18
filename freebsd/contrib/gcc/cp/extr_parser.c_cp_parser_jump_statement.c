#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum rid { ____Placeholder_rid } rid ;
struct TYPE_9__ {int keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_10__ {int in_statement; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_KEYWORD ; 
 int /*<<< orphan*/  CPP_MULT ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
#define  IN_ITERATION_STMT 134 
#define  IN_OMP_BLOCK 133 
#define  IN_OMP_FOR 132 
 int IN_SWITCH_STMT ; 
 int /*<<< orphan*/  NULL_TREE ; 
#define  RID_BREAK 131 
#define  RID_CONTINUE 130 
#define  RID_GOTO 129 
#define  RID_RETURN 128 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  cp_parser_expression (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cp_parser_identifier (TYPE_2__*) ; 
 TYPE_1__* cp_parser_require (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cur_block ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  finish_break_stmt () ; 
 int /*<<< orphan*/  finish_continue_stmt () ; 
 int /*<<< orphan*/  finish_goto_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_return_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 

__attribute__((used)) static tree
cp_parser_jump_statement (cp_parser* parser)
{
  tree statement = error_mark_node;
  cp_token *token;
  enum rid keyword;

  /* Peek at the next token.  */
  token = cp_parser_require (parser, CPP_KEYWORD, "jump-statement");
  if (!token)
    return error_mark_node;

  /* See what kind of keyword it is.  */
  keyword = token->keyword;
  switch (keyword)
    {
    case RID_BREAK:
      switch (parser->in_statement)
	{
	case 0:
	  error ("break statement not within loop or switch");
	  break;
	default:
	  gcc_assert ((parser->in_statement & IN_SWITCH_STMT)
		      || parser->in_statement == IN_ITERATION_STMT);
	  statement = finish_break_stmt ();
	  break;
	case IN_OMP_BLOCK:
	  error ("invalid exit from OpenMP structured block");
	  break;
	case IN_OMP_FOR:
	  error ("break statement used with OpenMP for loop");
	  break;
	}
      cp_parser_require (parser, CPP_SEMICOLON, "%<;%>");
      break;

    case RID_CONTINUE:
      switch (parser->in_statement & ~IN_SWITCH_STMT)
	{
	case 0:
	  error ("continue statement not within a loop");
	  break;
	case IN_ITERATION_STMT:
	case IN_OMP_FOR:
	  statement = finish_continue_stmt ();
	  break;
	case IN_OMP_BLOCK:
	  error ("invalid exit from OpenMP structured block");
	  break;
	default:
	  gcc_unreachable ();
	}
      cp_parser_require (parser, CPP_SEMICOLON, "%<;%>");
      break;

    case RID_RETURN:
      {
	tree expr;

	/* If the next token is a `;', then there is no
	   expression.  */
	if (cp_lexer_next_token_is_not (parser->lexer, CPP_SEMICOLON))
	  expr = cp_parser_expression (parser, /*cast_p=*/false);
	else
	  expr = NULL_TREE;
	/* Build the return-statement.  */
	statement = finish_return_stmt (expr);
	/* Look for the final `;'.  */
	cp_parser_require (parser, CPP_SEMICOLON, "%<;%>");
      }
      break;

    case RID_GOTO:
      /* APPLE LOCAL begin blocks 6040305 (cb) */
      if (cur_block)
	error ("goto not allowed in block literal");
      /* APPLE LOCAL end blocks 6040305 (cb) */
      /* Create the goto-statement.  */
      if (cp_lexer_next_token_is (parser->lexer, CPP_MULT))
	{
	  /* Issue a warning about this use of a GNU extension.  */
	  if (pedantic)
	    pedwarn ("ISO C++ forbids computed gotos");
	  /* Consume the '*' token.  */
	  cp_lexer_consume_token (parser->lexer);
	  /* Parse the dependent expression.  */
	  finish_goto_stmt (cp_parser_expression (parser, /*cast_p=*/false));
	}
      else
	finish_goto_stmt (cp_parser_identifier (parser));
      /* Look for the final `;'.  */
      cp_parser_require (parser, CPP_SEMICOLON, "%<;%>");
      break;

    default:
      cp_parser_error (parser, "expected jump-statement");
      break;
    }

  return statement;
}