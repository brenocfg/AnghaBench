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
struct affine_tree_combination {int dummy; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  ADDR_EXPR 133 
 int BITS_PER_UNIT ; 
#define  INTEGER_CST 132 
#define  MINUS_EXPR 131 
#define  MULT_EXPR 130 
#define  NEGATE_EXPR 129 
#define  PLUS_EXPR 128 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aff_combination_add (struct affine_tree_combination*,struct affine_tree_combination*) ; 
 int /*<<< orphan*/  aff_combination_add_elt (struct affine_tree_combination*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aff_combination_const (struct affine_tree_combination*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aff_combination_elt (struct affine_tree_combination*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aff_combination_scale (struct affine_tree_combination*,int) ; 
 int /*<<< orphan*/  build_fold_addr_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_inner_reference (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 int int_cst_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tree_to_aff_combination (tree expr, tree type,
			 struct affine_tree_combination *comb)
{
  struct affine_tree_combination tmp;
  enum tree_code code;
  tree cst, core, toffset;
  HOST_WIDE_INT bitpos, bitsize;
  enum machine_mode mode;
  int unsignedp, volatilep;

  STRIP_NOPS (expr);

  code = TREE_CODE (expr);
  switch (code)
    {
    case INTEGER_CST:
      aff_combination_const (comb, type, int_cst_value (expr));
      return;

    case PLUS_EXPR:
    case MINUS_EXPR:
      tree_to_aff_combination (TREE_OPERAND (expr, 0), type, comb);
      tree_to_aff_combination (TREE_OPERAND (expr, 1), type, &tmp);
      if (code == MINUS_EXPR)
	aff_combination_scale (&tmp, -1);
      aff_combination_add (comb, &tmp);
      return;

    case MULT_EXPR:
      cst = TREE_OPERAND (expr, 1);
      if (TREE_CODE (cst) != INTEGER_CST)
	break;
      tree_to_aff_combination (TREE_OPERAND (expr, 0), type, comb);
      aff_combination_scale (comb, int_cst_value (cst));
      return;

    case NEGATE_EXPR:
      tree_to_aff_combination (TREE_OPERAND (expr, 0), type, comb);
      aff_combination_scale (comb, -1);
      return;

    case ADDR_EXPR:
      core = get_inner_reference (TREE_OPERAND (expr, 0), &bitsize, &bitpos,
				  &toffset, &mode, &unsignedp, &volatilep,
				  false);
      if (bitpos % BITS_PER_UNIT != 0)
	break;
      aff_combination_const (comb, type, bitpos / BITS_PER_UNIT);
      core = build_fold_addr_expr (core);
      if (TREE_CODE (core) == ADDR_EXPR)
	aff_combination_add_elt (comb, core, 1);
      else
	{
	  tree_to_aff_combination (core, type, &tmp);
	  aff_combination_add (comb, &tmp);
	}
      if (toffset)
	{
	  tree_to_aff_combination (toffset, type, &tmp);
	  aff_combination_add (comb, &tmp);
	}
      return;

    default:
      break;
    }

  aff_combination_elt (comb, type, expr);
}