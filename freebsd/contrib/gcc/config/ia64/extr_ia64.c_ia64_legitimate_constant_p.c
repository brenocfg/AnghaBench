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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  CONST 133 
#define  CONST_DOUBLE 132 
 int CONST_DOUBLE_OK_FOR_G (int /*<<< orphan*/ ) ; 
#define  CONST_INT 131 
#define  CONST_VECTOR 130 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_CLASS (int) ; 
 int GET_MODE_SIZE (int) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 129 
 int /*<<< orphan*/  MODE_VECTOR_INT ; 
 int const PLUS ; 
#define  SYMBOL_REF 128 
 int V2SFmode ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aligned_offset_symbol_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  any_offset_symbol_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  function_operand (int /*<<< orphan*/ ,int) ; 
 int ia64_extra_constraint (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  tls_symbolic_operand_type (int /*<<< orphan*/ ) ; 

bool
ia64_legitimate_constant_p (rtx x)
{
  switch (GET_CODE (x))
    {
    case CONST_INT:
    case LABEL_REF:
      return true;

    case CONST_DOUBLE:
      if (GET_MODE (x) == VOIDmode)
	return true;
      return CONST_DOUBLE_OK_FOR_G (x);

    case CONST:
    case SYMBOL_REF:
      /* ??? Short term workaround for PR 28490.  We must make the code here
	 match the code in ia64_expand_move and move_operand, even though they
	 are both technically wrong.  */
      if (tls_symbolic_operand_type (x) == 0)
	{
	  HOST_WIDE_INT addend = 0;
	  rtx op = x;

	  if (GET_CODE (op) == CONST
	      && GET_CODE (XEXP (op, 0)) == PLUS
	      && GET_CODE (XEXP (XEXP (op, 0), 1)) == CONST_INT)
	    {
	      addend = INTVAL (XEXP (XEXP (op, 0), 1));
	      op = XEXP (XEXP (op, 0), 0);
	    }

          if (any_offset_symbol_operand (op, GET_MODE (op))
              || function_operand (op, GET_MODE (op)))
            return true;
	  if (aligned_offset_symbol_operand (op, GET_MODE (op)))
	    return (addend & 0x3fff) == 0;
	  return false;
	}
      return false;

    case CONST_VECTOR:
      {
	enum machine_mode mode = GET_MODE (x);

	if (mode == V2SFmode)
	  return ia64_extra_constraint (x, 'Y');

	return (GET_MODE_CLASS (mode) == MODE_VECTOR_INT
		&& GET_MODE_SIZE (mode) <= 8);
      }

    default:
      return false;
    }
}