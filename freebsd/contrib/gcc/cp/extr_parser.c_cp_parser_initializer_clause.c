#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_6__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;
typedef  int /*<<< orphan*/  CONSTRUCTOR_ELTS ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTRUCTOR ; 
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_constant_expression (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  cp_parser_initializer_list (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fold_non_dependent_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
cp_parser_initializer_clause (cp_parser* parser, bool* non_constant_p)
{
  tree initializer;

  /* Assume the expression is constant.  */
  *non_constant_p = false;

  /* If it is not a `{', then we are looking at an
     assignment-expression.  */
  if (cp_lexer_next_token_is_not (parser->lexer, CPP_OPEN_BRACE))
    {
      initializer
	= cp_parser_constant_expression (parser,
					/*allow_non_constant_p=*/true,
					non_constant_p);
      if (!*non_constant_p)
	initializer = fold_non_dependent_expr (initializer);
    }
  else
    {
      /* Consume the `{' token.  */
      cp_lexer_consume_token (parser->lexer);
      /* Create a CONSTRUCTOR to represent the braced-initializer.  */
      initializer = make_node (CONSTRUCTOR);
      /* If it's not a `}', then there is a non-trivial initializer.  */
      if (cp_lexer_next_token_is_not (parser->lexer, CPP_CLOSE_BRACE))
	{
	  /* Parse the initializer list.  */
	  CONSTRUCTOR_ELTS (initializer)
	    = cp_parser_initializer_list (parser, non_constant_p);
	  /* A trailing `,' token is allowed.  */
	  if (cp_lexer_next_token_is (parser->lexer, CPP_COMMA))
	    cp_lexer_consume_token (parser->lexer);
	}
      /* Now, there should be a trailing `}'.  */
      cp_parser_require (parser, CPP_CLOSE_BRACE, "`}'");
    }

  return initializer;
}