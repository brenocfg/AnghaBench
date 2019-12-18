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
#define  ALIGNOF_EXPR 134 
#define  DELETE_EXPR 133 
#define  NEW_EXPR 132 
#define  SIZEOF_EXPR 131 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
#define  UNARY_PLUS_EXPR 130 
#define  VEC_DELETE_EXPR 129 
#define  VEC_NEW_EXPR 128 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_unary_expression (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_cast_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_delete_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_cxx_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_new_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_type_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_plus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_unary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_unary_expression (cxx_pretty_printer *pp, tree t)
{
  enum tree_code code = TREE_CODE (t);
  switch (code)
    {
    case NEW_EXPR:
    case VEC_NEW_EXPR:
      pp_cxx_new_expression (pp, t);
      break;

    case DELETE_EXPR:
    case VEC_DELETE_EXPR:
      pp_cxx_delete_expression (pp, t);
      break;

    case SIZEOF_EXPR:
    case ALIGNOF_EXPR:
      pp_cxx_identifier (pp, code == SIZEOF_EXPR ? "sizeof" : "__alignof__");
      pp_cxx_whitespace (pp);
      if (TYPE_P (TREE_OPERAND (t, 0)))
	{
	  pp_cxx_left_paren (pp);
	  pp_cxx_type_id (pp, TREE_OPERAND (t, 0));
	  pp_cxx_right_paren (pp);
	}
      else
	pp_unary_expression (pp, TREE_OPERAND (t, 0));
      break;

    case UNARY_PLUS_EXPR:
      pp_plus (pp);
      pp_cxx_cast_expression (pp, TREE_OPERAND (t, 0));
      break;

    default:
      pp_c_unary_expression (pp_c_base (pp), t);
      break;
    }
}