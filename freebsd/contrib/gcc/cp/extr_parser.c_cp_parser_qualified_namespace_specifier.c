#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  cp_parser_global_scope_opt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cp_parser_namespace_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_nested_name_specifier_opt (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static tree
cp_parser_qualified_namespace_specifier (cp_parser* parser)
{
  /* Look for the optional `::'.  */
  cp_parser_global_scope_opt (parser,
			      /*current_scope_valid_p=*/false);

  /* Look for the optional nested-name-specifier.  */
  cp_parser_nested_name_specifier_opt (parser,
				       /*typename_keyword_p=*/false,
				       /*check_dependency_p=*/true,
				       /*type_p=*/false,
				       /*is_declaration=*/true);

  return cp_parser_namespace_name (parser);
}