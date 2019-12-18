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
struct TYPE_9__ {scalar_t__ type; int keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_10__ {int /*<<< orphan*/  in_switch_statement_p; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COLON ; 
 scalar_t__ CPP_ELLIPSIS ; 
 scalar_t__ CPP_KEYWORD ; 
 scalar_t__ CPP_NAME ; 
 int /*<<< orphan*/  NULL_TREE ; 
#define  RID_CASE 129 
#define  RID_DEFAULT 128 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_constant_expression (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  cp_parser_identifier (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  finish_case_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_label_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_label_for_labeled_statement (cp_parser* parser)
{
  cp_token *token;

  /* The next token should be an identifier.  */
  token = cp_lexer_peek_token (parser->lexer);
  if (token->type != CPP_NAME
      && token->type != CPP_KEYWORD)
    {
      cp_parser_error (parser, "expected labeled-statement");
      return;
    }

  switch (token->keyword)
    {
    case RID_CASE:
      {
	tree expr, expr_hi;
	cp_token *ellipsis;

	/* Consume the `case' token.  */
	cp_lexer_consume_token (parser->lexer);
	/* Parse the constant-expression.  */
	expr = cp_parser_constant_expression (parser,
					      /*allow_non_constant_p=*/false,
					      NULL);

	ellipsis = cp_lexer_peek_token (parser->lexer);
	if (ellipsis->type == CPP_ELLIPSIS)
	  {
	    /* Consume the `...' token.  */
	    cp_lexer_consume_token (parser->lexer);
	    expr_hi =
	      cp_parser_constant_expression (parser,
					     /*allow_non_constant_p=*/false,
					     NULL);
	    /* We don't need to emit warnings here, as the common code
	       will do this for us.  */
	  }
	else
	  expr_hi = NULL_TREE;

	if (parser->in_switch_statement_p)
	  finish_case_label (expr, expr_hi);
	else
	  error ("case label %qE not within a switch statement", expr);
      }
      break;

    case RID_DEFAULT:
      /* Consume the `default' token.  */
      cp_lexer_consume_token (parser->lexer);

      if (parser->in_switch_statement_p)
	finish_case_label (NULL_TREE, NULL_TREE);
      else
	error ("case label not within a switch statement");
      break;

    default:
      /* Anything else must be an ordinary label.  */
      finish_label_stmt (cp_parser_identifier (parser));
      break;
    }

  /* Require the `:' token.  */
  cp_parser_require (parser, CPP_COLON, "`:'");
}