#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_10__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;
struct TYPE_11__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CPP_COMPL ; 
 scalar_t__ CPP_SCOPE ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_TEMPLATE ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_9__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cp_parser_global_scope_opt (TYPE_1__*,int) ; 
 scalar_t__ cp_parser_nested_name_specifier_opt (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  cp_parser_template_id (TYPE_1__*,int,int,int) ; 
 scalar_t__ cp_parser_type_name (TYPE_1__*) ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static void
cp_parser_pseudo_destructor_name (cp_parser* parser,
				  tree* scope,
				  tree* type)
{
  bool nested_name_specifier_p;

  /* Assume that things will not work out.  */
  *type = error_mark_node;

  /* Look for the optional `::' operator.  */
  cp_parser_global_scope_opt (parser, /*current_scope_valid_p=*/true);
  /* Look for the optional nested-name-specifier.  */
  nested_name_specifier_p
    = (cp_parser_nested_name_specifier_opt (parser,
					    /*typename_keyword_p=*/false,
					    /*check_dependency_p=*/true,
					    /*type_p=*/false,
					    /*is_declaration=*/true)
       != NULL_TREE);
  /* Now, if we saw a nested-name-specifier, we might be doing the
     second production.  */
  if (nested_name_specifier_p
      && cp_lexer_next_token_is_keyword (parser->lexer, RID_TEMPLATE))
    {
      /* Consume the `template' keyword.  */
      cp_lexer_consume_token (parser->lexer);
      /* Parse the template-id.  */
      cp_parser_template_id (parser,
			     /*template_keyword_p=*/true,
			     /*check_dependency_p=*/false,
			     /*is_declaration=*/true);
      /* Look for the `::' token.  */
      cp_parser_require (parser, CPP_SCOPE, "`::'");
    }
  /* If the next token is not a `~', then there might be some
     additional qualification.  */
  else if (cp_lexer_next_token_is_not (parser->lexer, CPP_COMPL))
    {
      /* Look for the type-name.  */
      *scope = TREE_TYPE (cp_parser_type_name (parser));

      if (*scope == error_mark_node)
	return;

      /* If we don't have ::~, then something has gone wrong.  Since
	 the only caller of this function is looking for something
	 after `.' or `->' after a scalar type, most likely the
	 program is trying to get a member of a non-aggregate
	 type.  */
      if (cp_lexer_next_token_is_not (parser->lexer, CPP_SCOPE)
	  || cp_lexer_peek_nth_token (parser->lexer, 2)->type != CPP_COMPL)
	{
	  cp_parser_error (parser, "request for member of non-aggregate type");
	  return;
	}

      /* Look for the `::' token.  */
      cp_parser_require (parser, CPP_SCOPE, "`::'");
    }
  else
    *scope = NULL_TREE;

  /* Look for the `~'.  */
  cp_parser_require (parser, CPP_COMPL, "`~'");
  /* Look for the type-name again.  We are not responsible for
     checking that it matches the first type-name.  */
  *type = cp_parser_type_name (parser);
}