#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* tree ;
struct TYPE_8__ {int /*<<< orphan*/  lexer; void* object_scope; void* qualifying_scope; void* scope; } ;
typedef  TYPE_1__ cp_parser ;
struct TYPE_9__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_NAME ; 
 scalar_t__ CPP_SCOPE ; 
 scalar_t__ TYPE_P (void*) ; 
 int /*<<< orphan*/  class_type ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 void* cp_parser_class_name (TYPE_1__*,int,int,int /*<<< orphan*/ ,int,int,int) ; 
 void* cp_parser_namespace_name (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 void* error_mark_node ; 
 int /*<<< orphan*/  none_type ; 

__attribute__((used)) static tree
cp_parser_class_or_namespace_name (cp_parser *parser,
				   bool typename_keyword_p,
				   bool template_keyword_p,
				   bool check_dependency_p,
				   bool type_p,
				   bool is_declaration)
{
  tree saved_scope;
  tree saved_qualifying_scope;
  tree saved_object_scope;
  tree scope;
  bool only_class_p;

  /* Before we try to parse the class-name, we must save away the
     current PARSER->SCOPE since cp_parser_class_name will destroy
     it.  */
  saved_scope = parser->scope;
  saved_qualifying_scope = parser->qualifying_scope;
  saved_object_scope = parser->object_scope;
  /* Try for a class-name first.  If the SAVED_SCOPE is a type, then
     there is no need to look for a namespace-name.  */
  only_class_p = template_keyword_p || (saved_scope && TYPE_P (saved_scope));
  if (!only_class_p)
    cp_parser_parse_tentatively (parser);
  scope = cp_parser_class_name (parser,
				typename_keyword_p,
				template_keyword_p,
				type_p ? class_type : none_type,
				check_dependency_p,
				/*class_head_p=*/false,
				is_declaration);
  /* If that didn't work, try for a namespace-name.  */
  if (!only_class_p && !cp_parser_parse_definitely (parser))
    {
      /* Restore the saved scope.  */
      parser->scope = saved_scope;
      parser->qualifying_scope = saved_qualifying_scope;
      parser->object_scope = saved_object_scope;
      /* If we are not looking at an identifier followed by the scope
	 resolution operator, then this is not part of a
	 nested-name-specifier.  (Note that this function is only used
	 to parse the components of a nested-name-specifier.)  */
      if (cp_lexer_next_token_is_not (parser->lexer, CPP_NAME)
	  || cp_lexer_peek_nth_token (parser->lexer, 2)->type != CPP_SCOPE)
	return error_mark_node;
      scope = cp_parser_namespace_name (parser);
    }

  return scope;
}