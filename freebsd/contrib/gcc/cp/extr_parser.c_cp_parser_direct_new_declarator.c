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
typedef  scalar_t__ tree ;
struct TYPE_6__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;
typedef  int /*<<< orphan*/  cp_declarator ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_SQUARE ; 
 int /*<<< orphan*/  CPP_OPEN_SQUARE ; 
 int WANT_ENUM ; 
 int WANT_INT ; 
 scalar_t__ build_expr_type_conversion (int,scalar_t__,int) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_constant_expression (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ cp_parser_expression (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/ * make_array_declarator (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  processing_template_decl ; 

__attribute__((used)) static cp_declarator *
cp_parser_direct_new_declarator (cp_parser* parser)
{
  cp_declarator *declarator = NULL;

  while (true)
    {
      tree expression;

      /* Look for the opening `['.  */
      cp_parser_require (parser, CPP_OPEN_SQUARE, "`['");
      /* The first expression is not required to be constant.  */
      if (!declarator)
	{
	  expression = cp_parser_expression (parser, /*cast_p=*/false);
	  /* The standard requires that the expression have integral
	     type.  DR 74 adds enumeration types.  We believe that the
	     real intent is that these expressions be handled like the
	     expression in a `switch' condition, which also allows
	     classes with a single conversion to integral or
	     enumeration type.  */
	  if (!processing_template_decl)
	    {
	      expression
		= build_expr_type_conversion (WANT_INT | WANT_ENUM,
					      expression,
					      /*complain=*/true);
	      if (!expression)
		{
		  error ("expression in new-declarator must have integral "
			 "or enumeration type");
		  expression = error_mark_node;
		}
	    }
	}
      /* But all the other expressions must be.  */
      else
	expression
	  = cp_parser_constant_expression (parser,
					   /*allow_non_constant=*/false,
					   NULL);
      /* Look for the closing `]'.  */
      cp_parser_require (parser, CPP_CLOSE_SQUARE, "`]'");

      /* Add this bound to the declarator.  */
      declarator = make_array_declarator (declarator, expression);

      /* If the next token is not a `[', then there are no more
	 bounds.  */
      if (cp_lexer_next_token_is_not (parser->lexer, CPP_OPEN_SQUARE))
	break;
    }

  return declarator;
}