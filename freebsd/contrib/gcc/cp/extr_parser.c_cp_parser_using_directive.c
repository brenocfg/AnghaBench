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
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  RID_NAMESPACE ; 
 int /*<<< orphan*/  RID_USING ; 
 int /*<<< orphan*/  cp_parser_attributes_opt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_global_scope_opt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cp_parser_namespace_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_nested_name_specifier_opt (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  cp_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  parse_using_directive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_using_directive (cp_parser* parser)
{
  tree namespace_decl;
  tree attribs;

  /* Look for the `using' keyword.  */
  cp_parser_require_keyword (parser, RID_USING, "`using'");
  /* And the `namespace' keyword.  */
  cp_parser_require_keyword (parser, RID_NAMESPACE, "`namespace'");
  /* Look for the optional `::' operator.  */
  cp_parser_global_scope_opt (parser, /*current_scope_valid_p=*/false);
  /* And the optional nested-name-specifier.  */
  cp_parser_nested_name_specifier_opt (parser,
				       /*typename_keyword_p=*/false,
				       /*check_dependency_p=*/true,
				       /*type_p=*/false,
				       /*is_declaration=*/true);
  /* Get the namespace being used.  */
  namespace_decl = cp_parser_namespace_name (parser);
  /* And any specified attributes.  */
  attribs = cp_parser_attributes_opt (parser);
  /* Update the symbol table.  */
  parse_using_directive (namespace_decl, attribs);
  /* Look for the final `;'.  */
  cp_parser_require (parser, CPP_SEMICOLON, "`;'");
}