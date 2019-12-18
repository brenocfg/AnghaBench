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
 int /*<<< orphan*/  CONST0_RTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_INT ; 
 int /*<<< orphan*/  CONST_VECTOR ; 
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RTX_CLASS (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM ; 
 int /*<<< orphan*/  MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE_VECTOR_INT ; 
 int /*<<< orphan*/  RTX_AUTOINC ; 
 int /*<<< orphan*/  V2SFmode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ia64_const_double_ok_for_letter_p (int /*<<< orphan*/ ,char) ; 
 int ia64_const_ok_for_letter_p (int,char) ; 
 int /*<<< orphan*/  memory_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_in_progress ; 
 int /*<<< orphan*/  simplify_subreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int small_addr_symbolic_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
ia64_extra_constraint (rtx value, char c)
{
  switch (c)
    {
    case 'Q':
      /* Non-volatile memory for FP_REG loads/stores.  */
      return memory_operand(value, VOIDmode) && !MEM_VOLATILE_P (value);

    case 'R':
      /* 1..4 for shladd arguments.  */
      return (GET_CODE (value) == CONST_INT
	      && INTVAL (value) >= 1 && INTVAL (value) <= 4);

    case 'S':
      /* Non-post-inc memory for asms and other unsavory creatures.  */
      return (GET_CODE (value) == MEM
	      && GET_RTX_CLASS (GET_CODE (XEXP (value, 0))) != RTX_AUTOINC
	      && (reload_in_progress || memory_operand (value, VOIDmode)));

    case 'T':
      /* Symbol ref to small-address-area.  */
      return small_addr_symbolic_operand (value, VOIDmode);

    case 'U':
      /* Vector zero.  */
      return value == CONST0_RTX (GET_MODE (value));

    case 'W':
      /* An integer vector, such that conversion to an integer yields a
	 value appropriate for an integer 'J' constraint.  */
      if (GET_CODE (value) == CONST_VECTOR
	  && GET_MODE_CLASS (GET_MODE (value)) == MODE_VECTOR_INT)
	{
	  value = simplify_subreg (DImode, value, GET_MODE (value), 0);
	  return ia64_const_ok_for_letter_p (INTVAL (value), 'J');
	}
      return false;

    case 'Y':
      /* A V2SF vector containing elements that satisfy 'G'.  */
      return
	(GET_CODE (value) == CONST_VECTOR
	 && GET_MODE (value) == V2SFmode
	 && ia64_const_double_ok_for_letter_p (XVECEXP (value, 0, 0), 'G')
	 && ia64_const_double_ok_for_letter_p (XVECEXP (value, 0, 1), 'G'));

    default:
      return false;
    }
}