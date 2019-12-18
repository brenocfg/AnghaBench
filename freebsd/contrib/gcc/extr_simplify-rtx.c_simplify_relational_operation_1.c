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
 int BImode ; 
 scalar_t__ COMPARISON_P (scalar_t__) ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_INT ; 
 int EQ ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ INTEGRAL_MODE_P (int) ; 
 scalar_t__ INTVAL (scalar_t__) ; 
 int MINUS ; 
 scalar_t__ MODE_INT ; 
 int NE ; 
 scalar_t__ NULL_RTX ; 
 int PLUS ; 
 int STORE_FLAG_VALUE ; 
 int UNKNOWN ; 
 int VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int XOR ; 
 int /*<<< orphan*/  ZERO_EXTEND ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ flag_unsafe_math_optimizations ; 
 scalar_t__ lowpart_subreg (int,scalar_t__,int) ; 
 int nonzero_bits (scalar_t__,int) ; 
 int reversed_comparison_code (scalar_t__,scalar_t__) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  side_effects_p (scalar_t__) ; 
 scalar_t__ simplify_gen_binary (int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ simplify_gen_relational (int,int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ simplify_gen_unary (int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 scalar_t__ simplify_rtx (scalar_t__) ; 

__attribute__((used)) static rtx
simplify_relational_operation_1 (enum rtx_code code, enum machine_mode mode,
				 enum machine_mode cmp_mode, rtx op0, rtx op1)
{
  enum rtx_code op0code = GET_CODE (op0);

  if (GET_CODE (op1) == CONST_INT)
    {
      if (INTVAL (op1) == 0 && COMPARISON_P (op0))
	{
	  /* If op0 is a comparison, extract the comparison arguments
	     from it.  */
	  if (code == NE)
	    {
	      if (GET_MODE (op0) == mode)
		return simplify_rtx (op0);
	      else
		return simplify_gen_relational (GET_CODE (op0), mode, VOIDmode,
					        XEXP (op0, 0), XEXP (op0, 1));
	    }
	  else if (code == EQ)
	    {
	      enum rtx_code new_code = reversed_comparison_code (op0, NULL_RTX);
	      if (new_code != UNKNOWN)
	        return simplify_gen_relational (new_code, mode, VOIDmode,
					        XEXP (op0, 0), XEXP (op0, 1));
	    }
	}
    }

  /* (eq/ne (plus x cst1) cst2) simplifies to (eq/ne x (cst2 - cst1))  */
  if ((code == EQ || code == NE)
      && (op0code == PLUS || op0code == MINUS)
      && CONSTANT_P (op1)
      && CONSTANT_P (XEXP (op0, 1))
      && (INTEGRAL_MODE_P (cmp_mode) || flag_unsafe_math_optimizations))
    {
      rtx x = XEXP (op0, 0);
      rtx c = XEXP (op0, 1);

      c = simplify_gen_binary (op0code == PLUS ? MINUS : PLUS,
			       cmp_mode, op1, c);
      return simplify_gen_relational (code, mode, cmp_mode, x, c);
    }

  /* (ne:SI (zero_extract:SI FOO (const_int 1) BAR) (const_int 0))) is
     the same as (zero_extract:SI FOO (const_int 1) BAR).  */
  if (code == NE
      && op1 == const0_rtx
      && GET_MODE_CLASS (mode) == MODE_INT
      && cmp_mode != VOIDmode
      /* ??? Work-around BImode bugs in the ia64 backend.  */
      && mode != BImode
      && cmp_mode != BImode
      && nonzero_bits (op0, cmp_mode) == 1
      && STORE_FLAG_VALUE == 1)
    return GET_MODE_SIZE (mode) > GET_MODE_SIZE (cmp_mode)
	   ? simplify_gen_unary (ZERO_EXTEND, mode, op0, cmp_mode)
	   : lowpart_subreg (mode, op0, cmp_mode);

  /* (eq/ne (xor x y) 0) simplifies to (eq/ne x y).  */
  if ((code == EQ || code == NE)
      && op1 == const0_rtx
      && op0code == XOR)
    return simplify_gen_relational (code, mode, cmp_mode,
				    XEXP (op0, 0), XEXP (op0, 1));

  /* (eq/ne (xor x y) x) simplifies to (eq/ne y 0).  */
  if ((code == EQ || code == NE)
      && op0code == XOR
      && rtx_equal_p (XEXP (op0, 0), op1)
      && !side_effects_p (XEXP (op0, 0)))
    return simplify_gen_relational (code, mode, cmp_mode,
				    XEXP (op0, 1), const0_rtx);

  /* Likewise (eq/ne (xor x y) y) simplifies to (eq/ne x 0).  */
  if ((code == EQ || code == NE)
      && op0code == XOR
      && rtx_equal_p (XEXP (op0, 1), op1)
      && !side_effects_p (XEXP (op0, 1)))
    return simplify_gen_relational (code, mode, cmp_mode,
				    XEXP (op0, 0), const0_rtx);

  /* (eq/ne (xor x C1) C2) simplifies to (eq/ne x (C1^C2)).  */
  if ((code == EQ || code == NE)
      && op0code == XOR
      && (GET_CODE (op1) == CONST_INT
	  || GET_CODE (op1) == CONST_DOUBLE)
      && (GET_CODE (XEXP (op0, 1)) == CONST_INT
	  || GET_CODE (XEXP (op0, 1)) == CONST_DOUBLE))
    return simplify_gen_relational (code, mode, cmp_mode, XEXP (op0, 0),
				    simplify_gen_binary (XOR, cmp_mode,
							 XEXP (op0, 1), op1));

  return NULL_RTX;
}