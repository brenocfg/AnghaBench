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
typedef  int /*<<< orphan*/  rtvec ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ CC0_P (scalar_t__) ; 
 scalar_t__ COMPARE ; 
 scalar_t__ CONST0_RTX (int) ; 
 scalar_t__ CONST1_RTX (int) ; 
 scalar_t__ CONST_DOUBLE_FROM_REAL_VALUE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FLOAT_STORE_FLAG_VALUE (int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 int GET_MODE_NUNITS (int) ; 
 scalar_t__ MODE_CC ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ RTVEC_ELT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 scalar_t__ VECTOR_MODE_P (int) ; 
 scalar_t__ VECTOR_STORE_FLAG_VALUE (int) ; 
 int VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ avoid_constant_pool_reference (scalar_t__) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const1_rtx ; 
 scalar_t__ gen_rtx_raw_CONST_VECTOR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtvec_alloc (int) ; 
 scalar_t__ simplify_const_relational_operation (int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ simplify_relational_operation_1 (int,int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ swap_commutative_operands_p (scalar_t__,scalar_t__) ; 
 int swap_condition (int) ; 

rtx
simplify_relational_operation (enum rtx_code code, enum machine_mode mode,
			       enum machine_mode cmp_mode, rtx op0, rtx op1)
{
  rtx tem, trueop0, trueop1;

  if (cmp_mode == VOIDmode)
    cmp_mode = GET_MODE (op0);
  if (cmp_mode == VOIDmode)
    cmp_mode = GET_MODE (op1);

  tem = simplify_const_relational_operation (code, cmp_mode, op0, op1);
  if (tem)
    {
      if (SCALAR_FLOAT_MODE_P (mode))
	{
          if (tem == const0_rtx)
            return CONST0_RTX (mode);
#ifdef FLOAT_STORE_FLAG_VALUE
	  {
	    REAL_VALUE_TYPE val;
	    val = FLOAT_STORE_FLAG_VALUE (mode);
	    return CONST_DOUBLE_FROM_REAL_VALUE (val, mode);
	  }
#else
	  return NULL_RTX;
#endif 
	}
      if (VECTOR_MODE_P (mode))
	{
	  if (tem == const0_rtx)
	    return CONST0_RTX (mode);
#ifdef VECTOR_STORE_FLAG_VALUE
	  {
	    int i, units;
	    rtvec v;

	    rtx val = VECTOR_STORE_FLAG_VALUE (mode);
	    if (val == NULL_RTX)
	      return NULL_RTX;
	    if (val == const1_rtx)
	      return CONST1_RTX (mode);

	    units = GET_MODE_NUNITS (mode);
	    v = rtvec_alloc (units);
	    for (i = 0; i < units; i++)
	      RTVEC_ELT (v, i) = val;
	    return gen_rtx_raw_CONST_VECTOR (mode, v);
	  }
#else
	  return NULL_RTX;
#endif
	}

      return tem;
    }

  /* For the following tests, ensure const0_rtx is op1.  */
  if (swap_commutative_operands_p (op0, op1)
      || (op0 == const0_rtx && op1 != const0_rtx))
    tem = op0, op0 = op1, op1 = tem, code = swap_condition (code);

  /* If op0 is a compare, extract the comparison arguments from it.  */
  if (GET_CODE (op0) == COMPARE && op1 == const0_rtx)
    return simplify_relational_operation (code, mode, VOIDmode,
				          XEXP (op0, 0), XEXP (op0, 1));

  if (GET_MODE_CLASS (cmp_mode) == MODE_CC
      || CC0_P (op0))
    return NULL_RTX;

  trueop0 = avoid_constant_pool_reference (op0);
  trueop1 = avoid_constant_pool_reference (op1);
  return simplify_relational_operation_1 (code, mode, cmp_mode,
		  			  trueop0, trueop1);
}