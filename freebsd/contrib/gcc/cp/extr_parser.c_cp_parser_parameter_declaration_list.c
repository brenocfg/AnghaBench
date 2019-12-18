#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_14__ {int in_unbraced_linkage_specification_p; int /*<<< orphan*/  in_type_id_in_expr_p; int /*<<< orphan*/  in_template_argument_list_p; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_15__ {struct TYPE_15__* next; } ;
typedef  TYPE_3__ cp_parameter_declarator ;

/* Variables and functions */
 scalar_t__ CPP_CLOSE_PAREN ; 
 scalar_t__ CPP_COMMA ; 
 scalar_t__ CPP_ELLIPSIS ; 
 scalar_t__ CPP_OPEN_BRACE ; 
 scalar_t__ CPP_SEMICOLON ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cp_parser_commit_to_tentative_parse (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 TYPE_3__* cp_parser_parameter_declaration (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_closing_parenthesis (TYPE_2__*,int,int,int) ; 
 scalar_t__ cp_parser_uncommitted_to_tentative_parse_p (TYPE_2__*) ; 

__attribute__((used)) static cp_parameter_declarator *
cp_parser_parameter_declaration_list (cp_parser* parser, bool *is_error)
{
  cp_parameter_declarator *parameters = NULL;
  cp_parameter_declarator **tail = &parameters;
  bool saved_in_unbraced_linkage_specification_p;

  /* Assume all will go well.  */
  *is_error = false;
  /* The special considerations that apply to a function within an
     unbraced linkage specifications do not apply to the parameters
     to the function.  */
  saved_in_unbraced_linkage_specification_p 
    = parser->in_unbraced_linkage_specification_p;
  parser->in_unbraced_linkage_specification_p = false;

  /* Look for more parameters.  */
  while (true)
    {
      cp_parameter_declarator *parameter;
      bool parenthesized_p;
      /* Parse the parameter.  */
      parameter
	= cp_parser_parameter_declaration (parser,
					   /*template_parm_p=*/false,
					   &parenthesized_p);

      /* If a parse error occurred parsing the parameter declaration,
	 then the entire parameter-declaration-list is erroneous.  */
      if (!parameter)
	{
	  *is_error = true;
	  parameters = NULL;
	  break;
	}
      /* Add the new parameter to the list.  */
      *tail = parameter;
      tail = &parameter->next;

      /* Peek at the next token.  */
      if (cp_lexer_next_token_is (parser->lexer, CPP_CLOSE_PAREN)
	  || cp_lexer_next_token_is (parser->lexer, CPP_ELLIPSIS)
	  /* These are for Objective-C++ */
	  || cp_lexer_next_token_is (parser->lexer, CPP_SEMICOLON)
	  || cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE))
	/* The parameter-declaration-list is complete.  */
	break;
      else if (cp_lexer_next_token_is (parser->lexer, CPP_COMMA))
	{
	  cp_token *token;

	  /* Peek at the next token.  */
	  token = cp_lexer_peek_nth_token (parser->lexer, 2);
	  /* If it's an ellipsis, then the list is complete.  */
	  if (token->type == CPP_ELLIPSIS)
	    break;
	  /* Otherwise, there must be more parameters.  Consume the
	     `,'.  */
	  cp_lexer_consume_token (parser->lexer);
	  /* When parsing something like:

		int i(float f, double d)

	     we can tell after seeing the declaration for "f" that we
	     are not looking at an initialization of a variable "i",
	     but rather at the declaration of a function "i".

	     Due to the fact that the parsing of template arguments
	     (as specified to a template-id) requires backtracking we
	     cannot use this technique when inside a template argument
	     list.  */
	  if (!parser->in_template_argument_list_p
	      && !parser->in_type_id_in_expr_p
	      && cp_parser_uncommitted_to_tentative_parse_p (parser)
	      /* However, a parameter-declaration of the form
		 "foat(f)" (which is a valid declaration of a
		 parameter "f") can also be interpreted as an
		 expression (the conversion of "f" to "float").  */
	      && !parenthesized_p)
	    cp_parser_commit_to_tentative_parse (parser);
	}
      else
	{
	  cp_parser_error (parser, "expected %<,%> or %<...%>");
	  if (!cp_parser_uncommitted_to_tentative_parse_p (parser))
	    cp_parser_skip_to_closing_parenthesis (parser,
						   /*recovering=*/true,
						   /*or_comma=*/false,
						   /*consume_paren=*/false);
	  break;
	}
    }

  parser->in_unbraced_linkage_specification_p
    = saved_in_unbraced_linkage_specification_p;

  return parameters;
}