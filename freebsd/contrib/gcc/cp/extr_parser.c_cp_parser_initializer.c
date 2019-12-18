#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_8__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_9__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 scalar_t__ CPP_EQ ; 
 scalar_t__ CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  cp_parser_initializer_clause (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  cp_parser_parenthesized_expression_list (TYPE_2__*,int,int,int*) ; 
 int /*<<< orphan*/  error_mark_node ; 

__attribute__((used)) static tree
cp_parser_initializer (cp_parser* parser, bool* is_parenthesized_init,
		       bool* non_constant_p)
{
  cp_token *token;
  tree init;

  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);

  /* Let our caller know whether or not this initializer was
     parenthesized.  */
  *is_parenthesized_init = (token->type == CPP_OPEN_PAREN);
  /* Assume that the initializer is constant.  */
  *non_constant_p = false;

  if (token->type == CPP_EQ)
    {
      /* Consume the `='.  */
      cp_lexer_consume_token (parser->lexer);
      /* Parse the initializer-clause.  */
      init = cp_parser_initializer_clause (parser, non_constant_p);
    }
  else if (token->type == CPP_OPEN_PAREN)
    init = cp_parser_parenthesized_expression_list (parser, false,
						    /*cast_p=*/false,
						    non_constant_p);
  else
    {
      /* Anything else is an error.  */
      cp_parser_error (parser, "expected initializer");
      init = error_mark_node;
    }

  return init;
}