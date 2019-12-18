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
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_EOF ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  CPP_PRAGMA ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  RID_AT_PACKAGE ; 
 int /*<<< orphan*/  RID_AT_PRIVATE ; 
 int /*<<< orphan*/  RID_AT_PROTECTED ; 
 int /*<<< orphan*/  RID_AT_PUBLIC ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_pragma (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ c_parser_struct_declaration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_node (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ nreverse (scalar_t__) ; 
 int /*<<< orphan*/  objc_add_instance_variable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_set_visibility (int) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  pragma_external ; 

__attribute__((used)) static void
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  while (c_parser_next_token_is_not (parser, CPP_EOF))
    {
      tree decls;
      /* Parse any stray semicolon.  */
      if (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  if (pedantic)
	    pedwarn ("extra semicolon in struct or union specified");
	  c_parser_consume_token (parser);
	  continue;
	}
      /* Stop if at the end of the instance variables.  */
      if (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  break;
	}
      /* Parse any objc-visibility-spec.  */
      if (c_parser_next_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (2);
	  continue;
	}
      else if (c_parser_next_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (0);
	  continue;
	}
      else if (c_parser_next_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (1);
	  continue;
	}
      /* APPLE LOCAL begin radar 4564694 */
      else if (c_parser_next_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (3);
	  continue;
	}
      /* APPLE LOCAL end radar 4564694 */
      else if (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external);
	  continue;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser);
      {
	/* Comma-separated instance variables are chained together in
	   reverse order; add them one by one.  */
	tree ivar = nreverse (decls);
	for (; ivar; ivar = TREE_CHAIN (ivar))
	  objc_add_instance_variable (copy_node (ivar));
      }
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}