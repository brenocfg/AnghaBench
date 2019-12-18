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

/* Variables and functions */
#define  CONST 131 
#define  CONST_DOUBLE 130 
#define  CONST_VECTOR 129 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int PLUS ; 
 int /*<<< orphan*/  SCALAR_FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPARC_SYMBOL_REF_TLS_P (int /*<<< orphan*/ ) ; 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  SYMBOL_REF_TLS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_VIS ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const_zero_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
legitimate_constant_p (rtx x)
{
  rtx inner;

  switch (GET_CODE (x))
    {
    case SYMBOL_REF:
      /* TLS symbols are not constant.  */
      if (SYMBOL_REF_TLS_MODEL (x))
	return false;
      break;

    case CONST:
      inner = XEXP (x, 0);

      /* Offsets of TLS symbols are never valid.
	 Discourage CSE from creating them.  */
      if (GET_CODE (inner) == PLUS
	  && SPARC_SYMBOL_REF_TLS_P (XEXP (inner, 0)))
	return false;
      break;

    case CONST_DOUBLE:
      if (GET_MODE (x) == VOIDmode)
        return true;

      /* Floating point constants are generally not ok.
	 The only exception is 0.0 in VIS.  */
      if (TARGET_VIS
	  && SCALAR_FLOAT_MODE_P (GET_MODE (x))
	  && const_zero_operand (x, GET_MODE (x)))
	return true;

      return false;

    case CONST_VECTOR:
      /* Vector constants are generally not ok.
	 The only exception is 0 in VIS.  */
      if (TARGET_VIS
	  && const_zero_operand (x, GET_MODE (x)))
	return true;

      return false;

    default:
      break;
    }

  return true;
}