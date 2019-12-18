#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_10__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_TYPENAME ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_class_name (TYPE_1__*,int,int,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ cp_parser_global_scope_opt (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cp_parser_identifier (TYPE_1__*) ; 
 scalar_t__ cp_parser_nested_name_specifier_opt (TYPE_1__*,int,int,int,int) ; 
 int cp_parser_optional_template_keyword (TYPE_1__*) ; 
 scalar_t__ cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  none_type ; 

__attribute__((used)) static tree
cp_parser_mem_initializer_id (cp_parser* parser)
{
  bool global_scope_p;
  bool nested_name_specifier_p;
  bool template_p = false;
  tree id;

  /* `typename' is not allowed in this context ([temp.res]).  */
  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_TYPENAME))
    {
      error ("keyword %<typename%> not allowed in this context (a qualified "
	     "member initializer is implicitly a type)");
      cp_lexer_consume_token (parser->lexer);
    }
  /* Look for the optional `::' operator.  */
  global_scope_p
    = (cp_parser_global_scope_opt (parser,
				   /*current_scope_valid_p=*/false)
       != NULL_TREE);
  /* Look for the optional nested-name-specifier.  The simplest way to
     implement:

       [temp.res]

       The keyword `typename' is not permitted in a base-specifier or
       mem-initializer; in these contexts a qualified name that
       depends on a template-parameter is implicitly assumed to be a
       type name.

     is to assume that we have seen the `typename' keyword at this
     point.  */
  nested_name_specifier_p
    = (cp_parser_nested_name_specifier_opt (parser,
					    /*typename_keyword_p=*/true,
					    /*check_dependency_p=*/true,
					    /*type_p=*/true,
					    /*is_declaration=*/true)
       != NULL_TREE);
  if (nested_name_specifier_p)
    template_p = cp_parser_optional_template_keyword (parser);
  /* If there is a `::' operator or a nested-name-specifier, then we
     are definitely looking for a class-name.  */
  if (global_scope_p || nested_name_specifier_p)
    return cp_parser_class_name (parser,
				 /*typename_keyword_p=*/true,
				 /*template_keyword_p=*/template_p,
				 none_type,
				 /*check_dependency_p=*/true,
				 /*class_head_p=*/false,
				 /*is_declaration=*/true);
  /* Otherwise, we could also be looking for an ordinary identifier.  */
  cp_parser_parse_tentatively (parser);
  /* Try a class-name.  */
  id = cp_parser_class_name (parser,
			     /*typename_keyword_p=*/true,
			     /*template_keyword_p=*/false,
			     none_type,
			     /*check_dependency_p=*/true,
			     /*class_head_p=*/false,
			     /*is_declaration=*/true);
  /* If we found one, we're done.  */
  if (cp_parser_parse_definitely (parser))
    return id;
  /* Otherwise, look for an ordinary identifier.  */
  return cp_parser_identifier (parser);
}