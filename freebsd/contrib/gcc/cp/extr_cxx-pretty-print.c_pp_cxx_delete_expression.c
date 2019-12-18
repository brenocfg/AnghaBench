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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
#define  DELETE_EXPR 129 
 int /*<<< orphan*/  DELETE_EXPR_USE_GLOBAL (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  VEC_DELETE_EXPR 128 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_cast_expression (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_colon_colon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_left_bracket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_right_bracket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_delete_expression (cxx_pretty_printer *pp, tree t)
{
  enum tree_code code = TREE_CODE (t);
  switch (code)
    {
    case DELETE_EXPR:
    case VEC_DELETE_EXPR:
      if (DELETE_EXPR_USE_GLOBAL (t))
	pp_cxx_colon_colon (pp);
      pp_cxx_identifier (pp, "delete");
      if (code == VEC_DELETE_EXPR)
	{
	  pp_left_bracket (pp);
	  pp_right_bracket (pp);
	}
      pp_c_cast_expression (pp_c_base (pp), TREE_OPERAND (t, 0));
      break;

    default:
      pp_unsupported_tree (pp, t);
    }
}