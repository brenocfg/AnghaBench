#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
struct TYPE_2__ {scalar_t__ reg_rtx; scalar_t__ in; } ;

/* Variables and functions */
 int CODE_LABEL ; 
 int GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int /*<<< orphan*/  INSN_P (scalar_t__) ; 
 scalar_t__ INSN_UID (scalar_t__) ; 
 int JUMP_INSN ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 int REG ; 
 size_t REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  delete_insn (scalar_t__) ; 
 int n_reloads ; 
 scalar_t__ reg_referenced_p (scalar_t__,int /*<<< orphan*/ ) ; 
 int* reg_reloaded_contents ; 
 scalar_t__ reg_set_p (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ reload_first_uid ; 
 scalar_t__* reload_inherited ; 
 scalar_t__* reload_override_in ; 
 TYPE_1__* rld ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 
 scalar_t__* spill_reg_order ; 

__attribute__((used)) static void
delete_address_reloads_1 (rtx dead_insn, rtx x, rtx current_insn)
{
  rtx prev, set, dst, i2;
  int i, j;
  enum rtx_code code = GET_CODE (x);

  if (code != REG)
    {
      const char *fmt = GET_RTX_FORMAT (code);
      for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
	{
	  if (fmt[i] == 'e')
	    delete_address_reloads_1 (dead_insn, XEXP (x, i), current_insn);
	  else if (fmt[i] == 'E')
	    {
	      for (j = XVECLEN (x, i) - 1; j >= 0; j--)
		delete_address_reloads_1 (dead_insn, XVECEXP (x, i, j),
					  current_insn);
	    }
	}
      return;
    }

  if (spill_reg_order[REGNO (x)] < 0)
    return;

  /* Scan backwards for the insn that sets x.  This might be a way back due
     to inheritance.  */
  for (prev = PREV_INSN (dead_insn); prev; prev = PREV_INSN (prev))
    {
      code = GET_CODE (prev);
      if (code == CODE_LABEL || code == JUMP_INSN)
	return;
      if (!INSN_P (prev))
	continue;
      if (reg_set_p (x, PATTERN (prev)))
	break;
      if (reg_referenced_p (x, PATTERN (prev)))
	return;
    }
  if (! prev || INSN_UID (prev) < reload_first_uid)
    return;
  /* Check that PREV only sets the reload register.  */
  set = single_set (prev);
  if (! set)
    return;
  dst = SET_DEST (set);
  if (!REG_P (dst)
      || ! rtx_equal_p (dst, x))
    return;
  if (! reg_set_p (dst, PATTERN (dead_insn)))
    {
      /* Check if DST was used in a later insn -
	 it might have been inherited.  */
      for (i2 = NEXT_INSN (dead_insn); i2; i2 = NEXT_INSN (i2))
	{
	  if (LABEL_P (i2))
	    break;
	  if (! INSN_P (i2))
	    continue;
	  if (reg_referenced_p (dst, PATTERN (i2)))
	    {
	      /* If there is a reference to the register in the current insn,
		 it might be loaded in a non-inherited reload.  If no other
		 reload uses it, that means the register is set before
		 referenced.  */
	      if (i2 == current_insn)
		{
		  for (j = n_reloads - 1; j >= 0; j--)
		    if ((rld[j].reg_rtx == dst && reload_inherited[j])
			|| reload_override_in[j] == dst)
		      return;
		  for (j = n_reloads - 1; j >= 0; j--)
		    if (rld[j].in && rld[j].reg_rtx == dst)
		      break;
		  if (j >= 0)
		    break;
		}
	      return;
	    }
	  if (JUMP_P (i2))
	    break;
	  /* If DST is still live at CURRENT_INSN, check if it is used for
	     any reload.  Note that even if CURRENT_INSN sets DST, we still
	     have to check the reloads.  */
	  if (i2 == current_insn)
	    {
	      for (j = n_reloads - 1; j >= 0; j--)
		if ((rld[j].reg_rtx == dst && reload_inherited[j])
		    || reload_override_in[j] == dst)
		  return;
	      /* ??? We can't finish the loop here, because dst might be
		 allocated to a pseudo in this block if no reload in this
		 block needs any of the classes containing DST - see
		 spill_hard_reg.  There is no easy way to tell this, so we
		 have to scan till the end of the basic block.  */
	    }
	  if (reg_set_p (dst, PATTERN (i2)))
	    break;
	}
    }
  delete_address_reloads_1 (prev, SET_SRC (set), current_insn);
  reg_reloaded_contents[REGNO (dst)] = -1;
  delete_insn (prev);
}