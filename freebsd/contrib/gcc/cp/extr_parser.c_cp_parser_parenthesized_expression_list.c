#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_11__ {scalar_t__ value; } ;
struct TYPE_12__ {TYPE_1__ u; } ;
typedef  TYPE_2__ cp_token ;
struct TYPE_13__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_3__ cp_parser ;
struct TYPE_14__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_COMMA ; 
 scalar_t__ CPP_NAME ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 scalar_t__ NULL_TREE ; 
 TYPE_2__* cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_assignment_expression (TYPE_3__*,int) ; 
 scalar_t__ cp_parser_constant_expression (TYPE_3__*,int,int*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int cp_parser_skip_to_closing_parenthesis (TYPE_3__*,int,int,int) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_non_dependent_expr (scalar_t__) ; 
 scalar_t__ nreverse (scalar_t__) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
cp_parser_parenthesized_expression_list (cp_parser* parser,
					 bool is_attribute_list,
					 bool cast_p,
					 bool *non_constant_p)
{
  tree expression_list = NULL_TREE;
  bool fold_expr_p = is_attribute_list;
  tree identifier = NULL_TREE;

  /* Assume all the expressions will be constant.  */
  if (non_constant_p)
    *non_constant_p = false;

  if (!cp_parser_require (parser, CPP_OPEN_PAREN, "`('"))
    return error_mark_node;

  /* Consume expressions until there are no more.  */
  if (cp_lexer_next_token_is_not (parser->lexer, CPP_CLOSE_PAREN))
    while (true)
      {
	tree expr;

	/* At the beginning of attribute lists, check to see if the
	   next token is an identifier.  */
	if (is_attribute_list
	    && cp_lexer_peek_token (parser->lexer)->type == CPP_NAME)
	  {
	    cp_token *token;

	    /* Consume the identifier.  */
	    token = cp_lexer_consume_token (parser->lexer);
	    /* Save the identifier.  */
	    identifier = token->u.value;
	  }
	else
	  {
	    /* Parse the next assignment-expression.  */
	    if (non_constant_p)
	      {
		bool expr_non_constant_p;
		expr = (cp_parser_constant_expression
			(parser, /*allow_non_constant_p=*/true,
			 &expr_non_constant_p));
		if (expr_non_constant_p)
		  *non_constant_p = true;
	      }
	    else
	      expr = cp_parser_assignment_expression (parser, cast_p);

	    if (fold_expr_p)
	      expr = fold_non_dependent_expr (expr);

	     /* Add it to the list.  We add error_mark_node
		expressions to the list, so that we can still tell if
		the correct form for a parenthesized expression-list
		is found. That gives better errors.  */
	    expression_list = tree_cons (NULL_TREE, expr, expression_list);

	    if (expr == error_mark_node)
	      goto skip_comma;
	  }

	/* After the first item, attribute lists look the same as
	   expression lists.  */
	is_attribute_list = false;

      get_comma:;
	/* If the next token isn't a `,', then we are done.  */
	if (cp_lexer_next_token_is_not (parser->lexer, CPP_COMMA))
	  break;

	/* Otherwise, consume the `,' and keep going.  */
	cp_lexer_consume_token (parser->lexer);
      }

  if (!cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'"))
    {
      int ending;

    skip_comma:;
      /* We try and resync to an unnested comma, as that will give the
	 user better diagnostics.  */
      ending = cp_parser_skip_to_closing_parenthesis (parser,
						      /*recovering=*/true,
						      /*or_comma=*/true,
						      /*consume_paren=*/true);
      if (ending < 0)
	goto get_comma;
      if (!ending)
	return error_mark_node;
    }

  /* We built up the list in reverse order so we must reverse it now.  */
  expression_list = nreverse (expression_list);
  if (identifier)
    expression_list = tree_cons (NULL_TREE, identifier, expression_list);

  return expression_list;
}