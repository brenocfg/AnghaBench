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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_AT_OPTIONAL ; 
 int /*<<< orphan*/  RID_AT_REQUIRED ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_objc_method_decl (int /*<<< orphan*/ *) ; 
 int c_parser_objc_method_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  objc_add_method_declaration (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_method_attributes ; 
 int objc_pq_context ; 
 int /*<<< orphan*/  objc_set_method_opt (int) ; 
 int /*<<< orphan*/  objc_set_method_type (int) ; 

__attribute__((used)) static void
c_parser_objc_methodproto (c_parser *parser)
{
  /* APPLE LOCAL C* language */
  enum tree_code type;
  tree decl;
  /* APPLE LOCAL begin C* language */
  if (c_parser_next_token_is_keyword (parser, RID_AT_REQUIRED))
    {
      objc_set_method_opt (0);
      c_parser_consume_token (parser);
      return;
    }
  if (c_parser_next_token_is_keyword (parser, RID_AT_OPTIONAL))
    {
      objc_set_method_opt (1);
      c_parser_consume_token (parser);
      return;
    }
  /* APPLE LOCAL begin C* language */
  /* APPLE LOCAL C* language */
  type = c_parser_objc_method_type (parser);
  objc_set_method_type (type);
  /* Remember protocol qualifiers in prototypes.  */
  objc_pq_context = 1;
  decl = c_parser_objc_method_decl (parser);
  /* Forget protocol qualifiers here.  */
  objc_pq_context = 0;
  /* APPLE LOCAL begin radar 3803157 - objc attribute (in 4.2 c) */
  objc_add_method_declaration (decl, objc_method_attributes);
  objc_method_attributes = NULL_TREE;
  /* APPLE LOCAL end radar 3803157 - objc attribute (in 4.2 c) */
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}