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
 int GET_CODE (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ simplify_binary_operation (int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ simplify_gen_binary (int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ swap_commutative_operands_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static rtx
simplify_associative_operation (enum rtx_code code, enum machine_mode mode,
				rtx op0, rtx op1)
{
  rtx tem;

  /* Linearize the operator to the left.  */
  if (GET_CODE (op1) == code)
    {
      /* "(a op b) op (c op d)" becomes "((a op b) op c) op d)".  */
      if (GET_CODE (op0) == code)
	{
	  tem = simplify_gen_binary (code, mode, op0, XEXP (op1, 0));
	  return simplify_gen_binary (code, mode, tem, XEXP (op1, 1));
	}

      /* "a op (b op c)" becomes "(b op c) op a".  */
      if (! swap_commutative_operands_p (op1, op0))
	return simplify_gen_binary (code, mode, op1, op0);

      tem = op0;
      op0 = op1;
      op1 = tem;
    }

  if (GET_CODE (op0) == code)
    {
      /* Canonicalize "(x op c) op y" as "(x op y) op c".  */
      if (swap_commutative_operands_p (XEXP (op0, 1), op1))
	{
	  tem = simplify_gen_binary (code, mode, XEXP (op0, 0), op1);
	  return simplify_gen_binary (code, mode, tem, XEXP (op0, 1));
	}

      /* Attempt to simplify "(a op b) op c" as "a op (b op c)".  */
      tem = swap_commutative_operands_p (XEXP (op0, 1), op1)
	    ? simplify_binary_operation (code, mode, op1, XEXP (op0, 1))
	    : simplify_binary_operation (code, mode, XEXP (op0, 1), op1);
      if (tem != 0)
        return simplify_gen_binary (code, mode, XEXP (op0, 0), tem);

      /* Attempt to simplify "(a op b) op c" as "(a op c) op b".  */
      tem = swap_commutative_operands_p (XEXP (op0, 0), op1)
	    ? simplify_binary_operation (code, mode, op1, XEXP (op0, 0))
	    : simplify_binary_operation (code, mode, XEXP (op0, 0), op1);
      if (tem != 0)
        return simplify_gen_binary (code, mode, tem, XEXP (op0, 1));
    }

  return 0;
}