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
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_AT_PROPERTY ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ c_parser_component_decl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_objc_property_attr_decl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  copy_node (scalar_t__) ; 
 scalar_t__ nreverse (scalar_t__) ; 
 int /*<<< orphan*/  objc_add_property_variable (int /*<<< orphan*/ ) ; 
 int objc_property_attr_context ; 
 int /*<<< orphan*/  objc_set_property_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
c_parser_objc_property_declaration (c_parser *parser)
{
  tree prop;
  c_parser_require_keyword (parser, RID_AT_PROPERTY, "expected %<@property%>");
  objc_property_attr_context = 1;
  objc_set_property_attr (0, NULL_TREE);
  c_parser_objc_property_attr_decl (parser);
  objc_property_attr_context = 0;
  prop = c_parser_component_decl (parser);
  /* Comma-separated properties are chained together in
     reverse order; add them one by one.  */
  prop = nreverse (prop);

  for (; prop; prop = TREE_CHAIN (prop))
    objc_add_property_variable (copy_node (prop));
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}