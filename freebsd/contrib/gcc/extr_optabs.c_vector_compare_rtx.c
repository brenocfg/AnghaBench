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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
struct TYPE_4__ {TYPE_1__* operand; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* predicate ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARISON_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  force_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_rtx_code (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* insn_data ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static rtx
vector_compare_rtx (tree cond, bool unsignedp, enum insn_code icode)
{
  enum rtx_code rcode;
  tree t_op0, t_op1;
  rtx rtx_op0, rtx_op1;

  /* This is unlikely. While generating VEC_COND_EXPR, auto vectorizer
     ensures that condition is a relational operation.  */
  gcc_assert (COMPARISON_CLASS_P (cond));

  rcode = get_rtx_code (TREE_CODE (cond), unsignedp);
  t_op0 = TREE_OPERAND (cond, 0);
  t_op1 = TREE_OPERAND (cond, 1);

  /* Expand operands.  */
  rtx_op0 = expand_expr (t_op0, NULL_RTX, TYPE_MODE (TREE_TYPE (t_op0)), 1);
  rtx_op1 = expand_expr (t_op1, NULL_RTX, TYPE_MODE (TREE_TYPE (t_op1)), 1);

  if (!insn_data[icode].operand[4].predicate (rtx_op0, GET_MODE (rtx_op0))
      && GET_MODE (rtx_op0) != VOIDmode)
    rtx_op0 = force_reg (GET_MODE (rtx_op0), rtx_op0);

  if (!insn_data[icode].operand[5].predicate (rtx_op1, GET_MODE (rtx_op1))
      && GET_MODE (rtx_op1) != VOIDmode)
    rtx_op1 = force_reg (GET_MODE (rtx_op1), rtx_op1);

  return gen_rtx_fmt_ee (rcode, VOIDmode, rtx_op0, rtx_op1);
}