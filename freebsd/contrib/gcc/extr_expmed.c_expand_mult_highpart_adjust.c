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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ GET_MODE_BITSIZE (int) ; 
 int MINUS ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int PLUS ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  expand_and (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_shift (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
expand_mult_highpart_adjust (enum machine_mode mode, rtx adj_operand, rtx op0,
			     rtx op1, rtx target, int unsignedp)
{
  rtx tem;
  enum rtx_code adj_code = unsignedp ? PLUS : MINUS;

  tem = expand_shift (RSHIFT_EXPR, mode, op0,
		      build_int_cst (NULL_TREE, GET_MODE_BITSIZE (mode) - 1),
		      NULL_RTX, 0);
  tem = expand_and (mode, tem, op1, NULL_RTX);
  adj_operand
    = force_operand (gen_rtx_fmt_ee (adj_code, mode, adj_operand, tem),
		     adj_operand);

  tem = expand_shift (RSHIFT_EXPR, mode, op1,
		      build_int_cst (NULL_TREE, GET_MODE_BITSIZE (mode) - 1),
		      NULL_RTX, 0);
  tem = expand_and (mode, tem, op0, NULL_RTX);
  target = force_operand (gen_rtx_fmt_ee (adj_code, mode, adj_operand, tem),
			  target);

  return target;
}