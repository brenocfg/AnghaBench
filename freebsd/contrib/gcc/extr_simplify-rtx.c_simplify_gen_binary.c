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
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ GET_RTX_CLASS (int) ; 
 scalar_t__ RTX_COMM_ARITH ; 
 scalar_t__ gen_rtx_fmt_ee (int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ simplify_binary_operation (int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ swap_commutative_operands_p (scalar_t__,scalar_t__) ; 

rtx
simplify_gen_binary (enum rtx_code code, enum machine_mode mode, rtx op0,
		     rtx op1)
{
  rtx tem;

  /* If this simplifies, do it.  */
  tem = simplify_binary_operation (code, mode, op0, op1);
  if (tem)
    return tem;

  /* Put complex operands first and constants second if commutative.  */
  if (GET_RTX_CLASS (code) == RTX_COMM_ARITH
      && swap_commutative_operands_p (op0, op1))
    tem = op0, op0 = op1, op1 = tem;

  return gen_rtx_fmt_ee (code, mode, op0, op1);
}