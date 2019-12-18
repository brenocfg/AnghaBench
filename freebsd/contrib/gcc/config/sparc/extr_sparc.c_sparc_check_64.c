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

/* Variables and functions */
#define  CALL_INSN 132 
#define  CODE_LABEL 131 
 scalar_t__ DImode ; 
 int GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
#define  INSN 130 
#define  JUMP_INSN 129 
#define  NOTE 128 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 int REG ; 
 scalar_t__ REGNO (scalar_t__) ; 
 int REG_N_SETS (scalar_t__) ; 
 int SET ; 
 int /*<<< orphan*/  SET_DEST (scalar_t__) ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 scalar_t__ flag_expensive_optimizations ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_last_insn_anywhere () ; 
 int /*<<< orphan*/  reg_overlap_mentioned_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,int /*<<< orphan*/ ) ; 
 int set_extends (scalar_t__) ; 

int
sparc_check_64 (rtx x, rtx insn)
{
  /* If a register is set only once it is safe to ignore insns this
     code does not know how to handle.  The loop will either recognize
     the single set and return the correct value or fail to recognize
     it and return 0.  */
  int set_once = 0;
  rtx y = x;

  gcc_assert (GET_CODE (x) == REG);

  if (GET_MODE (x) == DImode)
    y = gen_rtx_REG (SImode, REGNO (x) + WORDS_BIG_ENDIAN);

  if (flag_expensive_optimizations
      && REG_N_SETS (REGNO (y)) == 1)
    set_once = 1;

  if (insn == 0)
    {
      if (set_once)
	insn = get_last_insn_anywhere ();
      else
	return 0;
    }

  while ((insn = PREV_INSN (insn)))
    {
      switch (GET_CODE (insn))
	{
	case JUMP_INSN:
	case NOTE:
	  break;
	case CODE_LABEL:
	case CALL_INSN:
	default:
	  if (! set_once)
	    return 0;
	  break;
	case INSN:
	  {
	    rtx pat = PATTERN (insn);
	    if (GET_CODE (pat) != SET)
	      return 0;
	    if (rtx_equal_p (x, SET_DEST (pat)))
	      return set_extends (insn);
	    if (y && rtx_equal_p (y, SET_DEST (pat)))
	      return set_extends (insn);
	    if (reg_overlap_mentioned_p (SET_DEST (pat), y))
	      return 0;
	  }
	}
    }
  return 0;
}