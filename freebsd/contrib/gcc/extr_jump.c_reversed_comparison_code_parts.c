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
 scalar_t__ CC0_P (scalar_t__) ; 
 scalar_t__ COMPARE ; 
 scalar_t__ CONST_INT ; 
#define  EQ 141 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ GET_RTX_CLASS (int) ; 
#define  GEU 140 
#define  GTU 139 
 int /*<<< orphan*/  HONOR_NANS (int) ; 
 int /*<<< orphan*/  LABEL_P (scalar_t__) ; 
#define  LEU 138 
#define  LTGT 137 
#define  LTU 136 
 scalar_t__ MODE_CC ; 
#define  NE 135 
#define  ORDERED 134 
 scalar_t__ REG_P (scalar_t__) ; 
 int REVERSE_CONDITION (int,int) ; 
 scalar_t__ REVERSIBLE_CC_MODE (int) ; 
 scalar_t__ RTX_COMM_COMPARE ; 
 scalar_t__ RTX_COMPARE ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
#define  UNEQ 133 
#define  UNGE 132 
#define  UNGT 131 
 int UNKNOWN ; 
#define  UNLE 130 
#define  UNLT 129 
#define  UNORDERED 128 
 int VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ prev_nonnote_insn (scalar_t__) ; 
 int reverse_condition (int) ; 
 int reverse_condition_maybe_unordered (int) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ set_of (scalar_t__,scalar_t__) ; 

enum rtx_code
reversed_comparison_code_parts (enum rtx_code code, rtx arg0, rtx arg1, rtx insn)
{
  enum machine_mode mode;

  /* If this is not actually a comparison, we can't reverse it.  */
  if (GET_RTX_CLASS (code) != RTX_COMPARE
      && GET_RTX_CLASS (code) != RTX_COMM_COMPARE)
    return UNKNOWN;

  mode = GET_MODE (arg0);
  if (mode == VOIDmode)
    mode = GET_MODE (arg1);

  /* First see if machine description supplies us way to reverse the
     comparison.  Give it priority over everything else to allow
     machine description to do tricks.  */
  if (GET_MODE_CLASS (mode) == MODE_CC
      && REVERSIBLE_CC_MODE (mode))
    {
#ifdef REVERSE_CONDITION
      return REVERSE_CONDITION (code, mode);
#endif
      return reverse_condition (code);
    }

  /* Try a few special cases based on the comparison code.  */
  switch (code)
    {
    case GEU:
    case GTU:
    case LEU:
    case LTU:
    case NE:
    case EQ:
      /* It is always safe to reverse EQ and NE, even for the floating
	 point.  Similarly the unsigned comparisons are never used for
	 floating point so we can reverse them in the default way.  */
      return reverse_condition (code);
    case ORDERED:
    case UNORDERED:
    case LTGT:
    case UNEQ:
      /* In case we already see unordered comparison, we can be sure to
	 be dealing with floating point so we don't need any more tests.  */
      return reverse_condition_maybe_unordered (code);
    case UNLT:
    case UNLE:
    case UNGT:
    case UNGE:
      /* We don't have safe way to reverse these yet.  */
      return UNKNOWN;
    default:
      break;
    }

  if (GET_MODE_CLASS (mode) == MODE_CC || CC0_P (arg0))
    {
      rtx prev;
      /* Try to search for the comparison to determine the real mode.
         This code is expensive, but with sane machine description it
         will be never used, since REVERSIBLE_CC_MODE will return true
         in all cases.  */
      if (! insn)
	return UNKNOWN;

      for (prev = prev_nonnote_insn (insn);
	   prev != 0 && !LABEL_P (prev);
	   prev = prev_nonnote_insn (prev))
	{
	  rtx set = set_of (arg0, prev);
	  if (set && GET_CODE (set) == SET
	      && rtx_equal_p (SET_DEST (set), arg0))
	    {
	      rtx src = SET_SRC (set);

	      if (GET_CODE (src) == COMPARE)
		{
		  rtx comparison = src;
		  arg0 = XEXP (src, 0);
		  mode = GET_MODE (arg0);
		  if (mode == VOIDmode)
		    mode = GET_MODE (XEXP (comparison, 1));
		  break;
		}
	      /* We can get past reg-reg moves.  This may be useful for model
	         of i387 comparisons that first move flag registers around.  */
	      if (REG_P (src))
		{
		  arg0 = src;
		  continue;
		}
	    }
	  /* If register is clobbered in some ununderstandable way,
	     give up.  */
	  if (set)
	    return UNKNOWN;
	}
    }

  /* Test for an integer condition, or a floating-point comparison
     in which NaNs can be ignored.  */
  if (GET_CODE (arg0) == CONST_INT
      || (GET_MODE (arg0) != VOIDmode
	  && GET_MODE_CLASS (mode) != MODE_CC
	  && !HONOR_NANS (mode)))
    return reverse_condition (code);

  return UNKNOWN;
}