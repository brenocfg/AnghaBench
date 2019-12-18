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
struct c_expr {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 scalar_t__ COMPOUND_LITERAL_EXPR ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 struct c_expr c_parser_braced_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct c_expr c_parser_expr_no_commas (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct c_expr default_function_array_conversion (struct c_expr) ; 

__attribute__((used)) static struct c_expr
c_parser_initializer (c_parser *parser)
{
  if (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    return c_parser_braced_init (parser, NULL_TREE, false);
  else
    {
      struct c_expr ret;
      ret = c_parser_expr_no_commas (parser, NULL);
      if (TREE_CODE (ret.value) != STRING_CST
	  && TREE_CODE (ret.value) != COMPOUND_LITERAL_EXPR)
	ret = default_function_array_conversion (ret);
      return ret;
    }
}