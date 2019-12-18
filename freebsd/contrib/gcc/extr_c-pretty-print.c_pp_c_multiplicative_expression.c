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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
#define  MULT_EXPR 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
#define  TRUNC_DIV_EXPR 129 
#define  TRUNC_MOD_EXPR 128 
 int /*<<< orphan*/  pp_c_cast_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_star (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_modulo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_multiplicative_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_slash (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_c_multiplicative_expression (c_pretty_printer *pp, tree e)
{
  enum tree_code code = TREE_CODE (e);
  switch (code)
    {
    case MULT_EXPR:
    case TRUNC_DIV_EXPR:
    case TRUNC_MOD_EXPR:
      pp_multiplicative_expression (pp, TREE_OPERAND (e, 0));
      pp_c_whitespace (pp);
      if (code == MULT_EXPR)
	pp_c_star (pp);
      else if (code == TRUNC_DIV_EXPR)
	pp_slash (pp);
      else
	pp_modulo (pp);
      pp_c_whitespace (pp);
      pp_c_cast_expression (pp, TREE_OPERAND (e, 1));
      break;

    default:
      pp_c_cast_expression (pp, e);
      break;
    }
}