#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {int /*<<< orphan*/  scope; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cp_parser_nested_name_specifier_opt (TYPE_1__*,int,int,int,int) ; 

__attribute__((used)) static tree
cp_parser_nested_name_specifier (cp_parser *parser,
				 bool typename_keyword_p,
				 bool check_dependency_p,
				 bool type_p,
				 bool is_declaration)
{
  tree scope;

  /* Look for the nested-name-specifier.  */
  scope = cp_parser_nested_name_specifier_opt (parser,
					       typename_keyword_p,
					       check_dependency_p,
					       type_p,
					       is_declaration);
  /* If it was not present, issue an error message.  */
  if (!scope)
    {
      cp_parser_error (parser, "expected nested-name-specifier");
      parser->scope = NULL_TREE;
    }

  return scope;
}