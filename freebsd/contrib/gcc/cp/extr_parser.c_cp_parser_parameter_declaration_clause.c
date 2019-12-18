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
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ type; scalar_t__ keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_14__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_15__ {int ellipsis_p; } ;
typedef  TYPE_3__ cp_parameter_declarator ;
struct TYPE_12__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CPP_CLOSE_PAREN ; 
 scalar_t__ CPP_COMMA ; 
 scalar_t__ CPP_ELLIPSIS ; 
 scalar_t__ RID_VOID ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_11__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 TYPE_3__* cp_parser_parameter_declaration_list (TYPE_2__*,int*) ; 
 int /*<<< orphan*/ * cp_parser_require (TYPE_2__*,scalar_t__,char*) ; 
 int /*<<< orphan*/ * current_class_type ; 
 scalar_t__ current_lang_name ; 
 scalar_t__ in_system_header ; 
 scalar_t__ lang_name_c ; 
 TYPE_3__* no_parameters ; 

__attribute__((used)) static cp_parameter_declarator *
cp_parser_parameter_declaration_clause (cp_parser* parser)
{
  cp_parameter_declarator *parameters;
  cp_token *token;
  bool ellipsis_p;
  bool is_error;

  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);
  /* Check for trivial parameter-declaration-clauses.  */
  if (token->type == CPP_ELLIPSIS)
    {
      /* Consume the `...' token.  */
      cp_lexer_consume_token (parser->lexer);
      return NULL;
    }
  else if (token->type == CPP_CLOSE_PAREN)
    /* There are no parameters.  */
    {
#ifndef NO_IMPLICIT_EXTERN_C
      if (in_system_header && current_class_type == NULL
	  && current_lang_name == lang_name_c)
	return NULL;
      else
#endif
	return no_parameters;
    }
  /* Check for `(void)', too, which is a special case.  */
  else if (token->keyword == RID_VOID
	   && (cp_lexer_peek_nth_token (parser->lexer, 2)->type
	       == CPP_CLOSE_PAREN))
    {
      /* Consume the `void' token.  */
      cp_lexer_consume_token (parser->lexer);
      /* There are no parameters.  */
      return no_parameters;
    }

  /* Parse the parameter-declaration-list.  */
  parameters = cp_parser_parameter_declaration_list (parser, &is_error);
  /* If a parse error occurred while parsing the
     parameter-declaration-list, then the entire
     parameter-declaration-clause is erroneous.  */
  if (is_error)
    return NULL;

  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);
  /* If it's a `,', the clause should terminate with an ellipsis.  */
  if (token->type == CPP_COMMA)
    {
      /* Consume the `,'.  */
      cp_lexer_consume_token (parser->lexer);
      /* Expect an ellipsis.  */
      ellipsis_p
	= (cp_parser_require (parser, CPP_ELLIPSIS, "`...'") != NULL);
    }
  /* It might also be `...' if the optional trailing `,' was
     omitted.  */
  else if (token->type == CPP_ELLIPSIS)
    {
      /* Consume the `...' token.  */
      cp_lexer_consume_token (parser->lexer);
      /* And remember that we saw it.  */
      ellipsis_p = true;
    }
  else
    ellipsis_p = false;

  /* Finish the parameter list.  */
  if (parameters && ellipsis_p)
    parameters->ellipsis_p = true;

  return parameters;
}