#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_3__ {int /*<<< orphan*/  location; scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COLON ; 
 int /*<<< orphan*/  CPP_ELLIPSIS ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_CASE ; 
 int /*<<< orphan*/  RID_DEFAULT ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_stmt (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ c_parser_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ c_parser_expr_no_commas (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  decl_attributes (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ define_label (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ do_case (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 

__attribute__((used)) static void
c_parser_label (c_parser *parser)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  tree label = NULL_TREE;
  if (c_parser_next_token_is_keyword (parser, RID_CASE))
    {
      tree exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = c_parser_expr_no_commas (parser, NULL).value;
      if (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (exp1, NULL_TREE);
	}
      else if (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = c_parser_expr_no_commas (parser, NULL).value;
	  if (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (exp1, exp2);
	}
      else
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  else if (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      if (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (NULL_TREE, NULL_TREE);
    }
  else
    {
      tree name = c_parser_peek_token (parser)->value;
      tree tlab;
      location_t loc2;
      tree attrs;
      gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
      loc2 = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      attrs = c_parser_attributes (parser);
      tlab = define_label (loc2, name);
      if (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  label = add_stmt (build_stmt (LABEL_EXPR, tlab));
	}
    }
  if (label)
    SET_EXPR_LOCATION (label, loc1);
}