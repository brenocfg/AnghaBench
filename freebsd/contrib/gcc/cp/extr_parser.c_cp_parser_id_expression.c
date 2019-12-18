#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  void* tree ;
struct TYPE_16__ {int type; int /*<<< orphan*/  keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_17__ {int /*<<< orphan*/  lexer; void* qualifying_scope; void* object_scope; void* scope; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
#define  CPP_KEYWORD 129 
#define  CPP_NAME 128 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_OPERATOR ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 scalar_t__ cp_parser_global_scope_opt (TYPE_2__*,int) ; 
 void* cp_parser_identifier (TYPE_2__*) ; 
 scalar_t__ cp_parser_nested_name_specifier_opt (TYPE_2__*,int,int,int,int) ; 
 int /*<<< orphan*/  cp_parser_nth_token_starts_template_argument_list_p (TYPE_2__*,int) ; 
 void* cp_parser_operator_function_id (TYPE_2__*) ; 
 int cp_parser_optional_template_keyword (TYPE_2__*) ; 
 scalar_t__ cp_parser_parse_definitely (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_2__*) ; 
 void* cp_parser_template_id (TYPE_2__*,int,int,int) ; 
 void* cp_parser_unqualified_id (TYPE_2__*,int,int,int,int) ; 
 void* error_mark_node ; 

__attribute__((used)) static tree
cp_parser_id_expression (cp_parser *parser,
			 bool template_keyword_p,
			 bool check_dependency_p,
			 bool *template_p,
			 bool declarator_p,
			 bool optional_p)
{
  bool global_scope_p;
  bool nested_name_specifier_p;

  /* Assume the `template' keyword was not used.  */
  if (template_p)
    *template_p = template_keyword_p;

  /* Look for the optional `::' operator.  */
  global_scope_p
    = (cp_parser_global_scope_opt (parser, /*current_scope_valid_p=*/false)
       != NULL_TREE);
  /* Look for the optional nested-name-specifier.  */
  nested_name_specifier_p
    = (cp_parser_nested_name_specifier_opt (parser,
					    /*typename_keyword_p=*/false,
					    check_dependency_p,
					    /*type_p=*/false,
					    declarator_p)
       != NULL_TREE);
  /* If there is a nested-name-specifier, then we are looking at
     the first qualified-id production.  */
  if (nested_name_specifier_p)
    {
      tree saved_scope;
      tree saved_object_scope;
      tree saved_qualifying_scope;
      tree unqualified_id;
      bool is_template;

      /* See if the next token is the `template' keyword.  */
      if (!template_p)
	template_p = &is_template;
      *template_p = cp_parser_optional_template_keyword (parser);
      /* Name lookup we do during the processing of the
	 unqualified-id might obliterate SCOPE.  */
      saved_scope = parser->scope;
      saved_object_scope = parser->object_scope;
      saved_qualifying_scope = parser->qualifying_scope;
      /* Process the final unqualified-id.  */
      unqualified_id = cp_parser_unqualified_id (parser, *template_p,
						 check_dependency_p,
						 declarator_p,
						 /*optional_p=*/false);
      /* Restore the SAVED_SCOPE for our caller.  */
      parser->scope = saved_scope;
      parser->object_scope = saved_object_scope;
      parser->qualifying_scope = saved_qualifying_scope;

      return unqualified_id;
    }
  /* Otherwise, if we are in global scope, then we are looking at one
     of the other qualified-id productions.  */
  else if (global_scope_p)
    {
      cp_token *token;
      tree id;

      /* Peek at the next token.  */
      token = cp_lexer_peek_token (parser->lexer);

      /* If it's an identifier, and the next token is not a "<", then
	 we can avoid the template-id case.  This is an optimization
	 for this common case.  */
      if (token->type == CPP_NAME
	  && !cp_parser_nth_token_starts_template_argument_list_p
	       (parser, 2))
	return cp_parser_identifier (parser);

      cp_parser_parse_tentatively (parser);
      /* Try a template-id.  */
      id = cp_parser_template_id (parser,
				  /*template_keyword_p=*/false,
				  /*check_dependency_p=*/true,
				  declarator_p);
      /* If that worked, we're done.  */
      if (cp_parser_parse_definitely (parser))
	return id;

      /* Peek at the next token.  (Changes in the token buffer may
	 have invalidated the pointer obtained above.)  */
      token = cp_lexer_peek_token (parser->lexer);

      switch (token->type)
	{
	case CPP_NAME:
	  return cp_parser_identifier (parser);

	case CPP_KEYWORD:
	  if (token->keyword == RID_OPERATOR)
	    return cp_parser_operator_function_id (parser);
	  /* Fall through.  */

	default:
	  cp_parser_error (parser, "expected id-expression");
	  return error_mark_node;
	}
    }
  else
    return cp_parser_unqualified_id (parser, template_keyword_p,
				     /*check_dependency_p=*/true,
				     declarator_p,
				     optional_p);
}