#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_10__ {int type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_11__ {int integral_constant_expression_p; int non_integral_constant_expression_p; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
typedef  int /*<<< orphan*/  cp_id_kind ;

/* Variables and functions */
#define  CPP_CLOSE_PAREN 130 
 int const CPP_COMMA ; 
 int const CPP_DEREF ; 
#define  CPP_DOT 129 
 int const CPP_OPEN_PAREN ; 
#define  CPP_OPEN_SQUARE 128 
 int /*<<< orphan*/  OFFSETOF_EXPR ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_static_cast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_postfix_dot_deref_expression (TYPE_2__*,int const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_postfix_open_square_expression (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_2__*,int const,char*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_closing_parenthesis (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  cp_parser_type_id (TYPE_2__*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  finish_offsetof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_pointer_node ; 
 scalar_t__ processing_template_decl ; 
 int /*<<< orphan*/  size_type_node ; 

__attribute__((used)) static tree
cp_parser_builtin_offsetof (cp_parser *parser)
{
  int save_ice_p, save_non_ice_p;
  tree type, expr;
  cp_id_kind dummy;

  /* We're about to accept non-integral-constant things, but will
     definitely yield an integral constant expression.  Save and
     restore these values around our local parsing.  */
  save_ice_p = parser->integral_constant_expression_p;
  save_non_ice_p = parser->non_integral_constant_expression_p;

  /* Consume the "__builtin_offsetof" token.  */
  cp_lexer_consume_token (parser->lexer);
  /* Consume the opening `('.  */
  cp_parser_require (parser, CPP_OPEN_PAREN, "`('");
  /* Parse the type-id.  */
  type = cp_parser_type_id (parser);
  /* Look for the `,'.  */
  cp_parser_require (parser, CPP_COMMA, "`,'");

  /* Build the (type *)null that begins the traditional offsetof macro.  */
  expr = build_static_cast (build_pointer_type (type), null_pointer_node);

  /* Parse the offsetof-member-designator.  We begin as if we saw "expr->".  */
  expr = cp_parser_postfix_dot_deref_expression (parser, CPP_DEREF, expr,
						 true, &dummy);
  while (true)
    {
      cp_token *token = cp_lexer_peek_token (parser->lexer);
      switch (token->type)
	{
	case CPP_OPEN_SQUARE:
	  /* offsetof-member-designator "[" expression "]" */
	  expr = cp_parser_postfix_open_square_expression (parser, expr, true);
	  break;

	case CPP_DOT:
	  /* offsetof-member-designator "." identifier */
	  cp_lexer_consume_token (parser->lexer);
	  expr = cp_parser_postfix_dot_deref_expression (parser, CPP_DOT, expr,
							 true, &dummy);
	  break;

	case CPP_CLOSE_PAREN:
	  /* Consume the ")" token.  */
	  cp_lexer_consume_token (parser->lexer);
	  goto success;

	default:
	  /* Error.  We know the following require will fail, but
	     that gives the proper error message.  */
	  cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'");
	  cp_parser_skip_to_closing_parenthesis (parser, true, false, true);
	  expr = error_mark_node;
	  goto failure;
	}
    }

 success:
  /* If we're processing a template, we can't finish the semantics yet.
     Otherwise we can fold the entire expression now.  */
  if (processing_template_decl)
    expr = build1 (OFFSETOF_EXPR, size_type_node, expr);
  else
    expr = finish_offsetof (expr);

 failure:
  parser->integral_constant_expression_p = save_ice_p;
  parser->non_integral_constant_expression_p = save_non_ice_p;

  return expr;
}