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

/* Variables and functions */
#define  AND 134 
#define  ASHIFT 133 
#define  ASHIFTRT 132 
 scalar_t__ COMMUTATIVE_ARITH_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
#define  IOR 131 
#define  LSHIFTRT 130 
 int MINUS ; 
#define  MULT 129 
 int /*<<< orphan*/  NOT ; 
 scalar_t__ OBJECT_P (int /*<<< orphan*/ ) ; 
 int PLUS ; 
#define  SUBREG 128 
 int /*<<< orphan*/  SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRULY_NOOP_TRUNCATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNITS_PER_WORD ; 
 int /*<<< orphan*/  VECTOR_MODE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int XOR ; 
 int /*<<< orphan*/  expand_compound_operation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_unsafe_math_optimizations ; 
 int /*<<< orphan*/  gen_lowpart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_binary (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_unary (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreg_lowpart_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
apply_distributive_law (rtx x)
{
  enum rtx_code code = GET_CODE (x);
  enum rtx_code inner_code;
  rtx lhs, rhs, other;
  rtx tem;

  /* Distributivity is not true for floating point as it can change the
     value.  So we don't do it unless -funsafe-math-optimizations.  */
  if (FLOAT_MODE_P (GET_MODE (x))
      && ! flag_unsafe_math_optimizations)
    return x;

  /* The outer operation can only be one of the following:  */
  if (code != IOR && code != AND && code != XOR
      && code != PLUS && code != MINUS)
    return x;

  lhs = XEXP (x, 0);
  rhs = XEXP (x, 1);

  /* If either operand is a primitive we can't do anything, so get out
     fast.  */
  if (OBJECT_P (lhs) || OBJECT_P (rhs))
    return x;

  lhs = expand_compound_operation (lhs);
  rhs = expand_compound_operation (rhs);
  inner_code = GET_CODE (lhs);
  if (inner_code != GET_CODE (rhs))
    return x;

  /* See if the inner and outer operations distribute.  */
  switch (inner_code)
    {
    case LSHIFTRT:
    case ASHIFTRT:
    case AND:
    case IOR:
      /* These all distribute except over PLUS.  */
      if (code == PLUS || code == MINUS)
	return x;
      break;

    case MULT:
      if (code != PLUS && code != MINUS)
	return x;
      break;

    case ASHIFT:
      /* This is also a multiply, so it distributes over everything.  */
      break;

    case SUBREG:
      /* Non-paradoxical SUBREGs distributes over all operations,
	 provided the inner modes and byte offsets are the same, this
	 is an extraction of a low-order part, we don't convert an fp
	 operation to int or vice versa, this is not a vector mode,
	 and we would not be converting a single-word operation into a
	 multi-word operation.  The latter test is not required, but
	 it prevents generating unneeded multi-word operations.  Some
	 of the previous tests are redundant given the latter test,
	 but are retained because they are required for correctness.

	 We produce the result slightly differently in this case.  */

      if (GET_MODE (SUBREG_REG (lhs)) != GET_MODE (SUBREG_REG (rhs))
	  || SUBREG_BYTE (lhs) != SUBREG_BYTE (rhs)
	  || ! subreg_lowpart_p (lhs)
	  || (GET_MODE_CLASS (GET_MODE (lhs))
	      != GET_MODE_CLASS (GET_MODE (SUBREG_REG (lhs))))
	  || (GET_MODE_SIZE (GET_MODE (lhs))
	      > GET_MODE_SIZE (GET_MODE (SUBREG_REG (lhs))))
	  || VECTOR_MODE_P (GET_MODE (lhs))
	  || GET_MODE_SIZE (GET_MODE (SUBREG_REG (lhs))) > UNITS_PER_WORD
	  /* Result might need to be truncated.  Don't change mode if
	     explicit truncation is needed.  */
	  || !TRULY_NOOP_TRUNCATION
	       (GET_MODE_BITSIZE (GET_MODE (x)),
		GET_MODE_BITSIZE (GET_MODE (SUBREG_REG (lhs)))))
	return x;

      tem = simplify_gen_binary (code, GET_MODE (SUBREG_REG (lhs)),
				 SUBREG_REG (lhs), SUBREG_REG (rhs));
      return gen_lowpart (GET_MODE (x), tem);

    default:
      return x;
    }

  /* Set LHS and RHS to the inner operands (A and B in the example
     above) and set OTHER to the common operand (C in the example).
     There is only one way to do this unless the inner operation is
     commutative.  */
  if (COMMUTATIVE_ARITH_P (lhs)
      && rtx_equal_p (XEXP (lhs, 0), XEXP (rhs, 0)))
    other = XEXP (lhs, 0), lhs = XEXP (lhs, 1), rhs = XEXP (rhs, 1);
  else if (COMMUTATIVE_ARITH_P (lhs)
	   && rtx_equal_p (XEXP (lhs, 0), XEXP (rhs, 1)))
    other = XEXP (lhs, 0), lhs = XEXP (lhs, 1), rhs = XEXP (rhs, 0);
  else if (COMMUTATIVE_ARITH_P (lhs)
	   && rtx_equal_p (XEXP (lhs, 1), XEXP (rhs, 0)))
    other = XEXP (lhs, 1), lhs = XEXP (lhs, 0), rhs = XEXP (rhs, 1);
  else if (rtx_equal_p (XEXP (lhs, 1), XEXP (rhs, 1)))
    other = XEXP (lhs, 1), lhs = XEXP (lhs, 0), rhs = XEXP (rhs, 0);
  else
    return x;

  /* Form the new inner operation, seeing if it simplifies first.  */
  tem = simplify_gen_binary (code, GET_MODE (x), lhs, rhs);

  /* There is one exception to the general way of distributing:
     (a | c) ^ (b | c) -> (a ^ b) & ~c  */
  if (code == XOR && inner_code == IOR)
    {
      inner_code = AND;
      other = simplify_gen_unary (NOT, GET_MODE (x), other, GET_MODE (x));
    }

  /* We may be able to continuing distributing the result, so call
     ourselves recursively on the inner operation before forming the
     outer operation, which we return.  */
  return simplify_gen_binary (inner_code, GET_MODE (x),
			      apply_distributive_law (tem), other);
}