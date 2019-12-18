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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_EQ ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  RID_NAMESPACE ; 
 scalar_t__ cp_parser_identifier (int /*<<< orphan*/ *) ; 
 scalar_t__ cp_parser_qualified_namespace_specifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_namespace_alias (scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static void
cp_parser_namespace_alias_definition (cp_parser* parser)
{
  tree identifier;
  tree namespace_specifier;

  /* Look for the `namespace' keyword.  */
  cp_parser_require_keyword (parser, RID_NAMESPACE, "`namespace'");
  /* Look for the identifier.  */
  identifier = cp_parser_identifier (parser);
  if (identifier == error_mark_node)
    return;
  /* Look for the `=' token.  */
  cp_parser_require (parser, CPP_EQ, "`='");
  /* Look for the qualified-namespace-specifier.  */
  namespace_specifier
    = cp_parser_qualified_namespace_specifier (parser);
  /* Look for the `;' token.  */
  cp_parser_require (parser, CPP_SEMICOLON, "`;'");

  /* Register the alias in the symbol table.  */
  do_namespace_alias (identifier, namespace_specifier);
}