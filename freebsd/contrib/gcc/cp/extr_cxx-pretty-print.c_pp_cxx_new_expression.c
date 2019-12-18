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
#define  NEW_EXPR 129 
 int /*<<< orphan*/  NEW_EXPR_USE_GLOBAL (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_LIST ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
#define  VEC_NEW_EXPR 128 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_expression_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_call_argument_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_colon_colon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_cxx_type_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_zero_node ; 

__attribute__((used)) static void
pp_cxx_new_expression (cxx_pretty_printer *pp, tree t)
{
  enum tree_code code = TREE_CODE (t);
  switch (code)
    {
    case NEW_EXPR:
    case VEC_NEW_EXPR:
      if (NEW_EXPR_USE_GLOBAL (t))
	pp_cxx_colon_colon (pp);
      pp_cxx_identifier (pp, "new");
      if (TREE_OPERAND (t, 0))
	{
	  pp_cxx_call_argument_list (pp, TREE_OPERAND (t, 0));
	  pp_space (pp);
	}
      /* FIXME: array-types are built with one more element.  */
      pp_cxx_type_id (pp, TREE_OPERAND (t, 1));
      if (TREE_OPERAND (t, 2))
	{
	  pp_left_paren (pp);
	  t = TREE_OPERAND (t, 2);
	  if (TREE_CODE (t) == TREE_LIST)
	    pp_c_expression_list (pp_c_base (pp), t);
	  else if (t == void_zero_node)
	    ;			/* OK, empty initializer list.  */
	  else
	    pp_cxx_expression (pp, t);
	  pp_right_paren (pp);
	}
      break;

    default:
      pp_unsupported_tree (pp, t);
    }
}