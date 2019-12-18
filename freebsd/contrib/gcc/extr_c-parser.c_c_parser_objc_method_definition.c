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
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_compound_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_objc_method_decl (int /*<<< orphan*/ *) ; 
 int c_parser_objc_method_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  objc_finish_method_definition (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_method_attributes ; 
 int objc_pq_context ; 
 int /*<<< orphan*/  objc_set_method_type (int) ; 
 int /*<<< orphan*/  objc_start_method_definition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 

__attribute__((used)) static void
c_parser_objc_method_definition (c_parser *parser)
{
  enum tree_code type = c_parser_objc_method_type (parser);
  tree decl;
  objc_set_method_type (type);
  objc_pq_context = 1;
  decl = c_parser_objc_method_decl (parser);
  if (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      if (pedantic)
	pedwarn ("extra semicolon in method definition specified");
    }
  if (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      return;
    }
  objc_pq_context = 0;
  /* APPLE LOCAL begin radar 3803157 - objc attribute (in 4.2 a) */
  objc_start_method_definition (decl, objc_method_attributes);
  objc_method_attributes = NULL_TREE;
  /* APPLE LOCAL end radar 3803157 - objc attribute (in 4.2 a) */
  add_stmt (c_parser_compound_statement (parser));
  objc_finish_method_definition (current_function_decl);
}