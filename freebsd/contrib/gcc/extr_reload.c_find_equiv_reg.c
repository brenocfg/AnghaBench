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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {scalar_t__ reg_rtx; scalar_t__ in; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CALL_INSN_FUNCTION_USAGE (scalar_t__) ; 
 scalar_t__ CALL_P (scalar_t__) ; 
 scalar_t__ CLOBBER ; 
 scalar_t__ COND_EXEC ; 
 scalar_t__ COND_EXEC_CODE (scalar_t__) ; 
 int /*<<< orphan*/  CONSTANT_ADDRESS_P (scalar_t__) ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_INT ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 size_t GET_MODE (scalar_t__) ; 
 scalar_t__ HARD_REGNO_CALL_PART_CLOBBERED (int,int) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ INSN_UID (scalar_t__) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ MEM_VOLATILE_P (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PARAM_MAX_RELOAD_SEARCH_INSNS ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ PLUS ; 
#define  POST_DEC 133 
#define  POST_INC 132 
#define  POST_MODIFY 131 
 scalar_t__ PREV_INSN (scalar_t__) ; 
#define  PRE_DEC 130 
#define  PRE_INC 129 
#define  PRE_MODIFY 128 
 unsigned int REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_EQUIV ; 
 scalar_t__ REG_INC ; 
 scalar_t__ REG_NOTES (scalar_t__) ; 
 scalar_t__ REG_NOTE_KIND (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  REG_UNUSED ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (size_t) ; 
 scalar_t__ SET ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 int STACK_POINTER_REGNUM ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ZERO_EXTRACT ; 
 scalar_t__* call_used_regs ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ flag_float_store ; 
 scalar_t__ frame_pointer_rtx ; 
 int** hard_regno_nregs ; 
 int n_reloads ; 
 scalar_t__ operand_subword (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ push_operand (scalar_t__,size_t) ; 
 scalar_t__ refers_to_regno_for_reload_p (int,int,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/ * reg_class_contents ; 
 scalar_t__* reg_equiv_memory_loc ; 
 scalar_t__ reg_overlap_mentioned_for_reload_p (scalar_t__,scalar_t__) ; 
 scalar_t__ reload_first_uid ; 
 TYPE_1__* rld ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ rtx_renumbered_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 
 scalar_t__ stack_pointer_rtx ; 
 int true_regnum (scalar_t__) ; 
 scalar_t__ volatile_insn_p (scalar_t__) ; 

rtx
find_equiv_reg (rtx goal, rtx insn, enum reg_class class, int other,
		short *reload_reg_p, int goalreg, enum machine_mode mode)
{
  rtx p = insn;
  rtx goaltry, valtry, value, where;
  rtx pat;
  int regno = -1;
  int valueno;
  int goal_mem = 0;
  int goal_const = 0;
  int goal_mem_addr_varies = 0;
  int need_stable_sp = 0;
  int nregs;
  int valuenregs;
  int num = 0;

  if (goal == 0)
    regno = goalreg;
  else if (REG_P (goal))
    regno = REGNO (goal);
  else if (MEM_P (goal))
    {
      enum rtx_code code = GET_CODE (XEXP (goal, 0));
      if (MEM_VOLATILE_P (goal))
	return 0;
      if (flag_float_store && SCALAR_FLOAT_MODE_P (GET_MODE (goal)))
	return 0;
      /* An address with side effects must be reexecuted.  */
      switch (code)
	{
	case POST_INC:
	case PRE_INC:
	case POST_DEC:
	case PRE_DEC:
	case POST_MODIFY:
	case PRE_MODIFY:
	  return 0;
	default:
	  break;
	}
      goal_mem = 1;
    }
  else if (CONSTANT_P (goal))
    goal_const = 1;
  else if (GET_CODE (goal) == PLUS
	   && XEXP (goal, 0) == stack_pointer_rtx
	   && CONSTANT_P (XEXP (goal, 1)))
    goal_const = need_stable_sp = 1;
  else if (GET_CODE (goal) == PLUS
	   && XEXP (goal, 0) == frame_pointer_rtx
	   && CONSTANT_P (XEXP (goal, 1)))
    goal_const = 1;
  else
    return 0;

  num = 0;
  /* Scan insns back from INSN, looking for one that copies
     a value into or out of GOAL.
     Stop and give up if we reach a label.  */

  while (1)
    {
      p = PREV_INSN (p);
      num++;
      if (p == 0 || LABEL_P (p)
	  || num > PARAM_VALUE (PARAM_MAX_RELOAD_SEARCH_INSNS))
	return 0;

      if (NONJUMP_INSN_P (p)
	  /* If we don't want spill regs ...  */
	  && (! (reload_reg_p != 0
		 && reload_reg_p != (short *) (HOST_WIDE_INT) 1)
	      /* ... then ignore insns introduced by reload; they aren't
		 useful and can cause results in reload_as_needed to be
		 different from what they were when calculating the need for
		 spills.  If we notice an input-reload insn here, we will
		 reject it below, but it might hide a usable equivalent.
		 That makes bad code.  It may even fail: perhaps no reg was
		 spilled for this insn because it was assumed we would find
		 that equivalent.  */
	      || INSN_UID (p) < reload_first_uid))
	{
	  rtx tem;
	  pat = single_set (p);

	  /* First check for something that sets some reg equal to GOAL.  */
	  if (pat != 0
	      && ((regno >= 0
		   && true_regnum (SET_SRC (pat)) == regno
		   && (valueno = true_regnum (valtry = SET_DEST (pat))) >= 0)
		  ||
		  (regno >= 0
		   && true_regnum (SET_DEST (pat)) == regno
		   && (valueno = true_regnum (valtry = SET_SRC (pat))) >= 0)
		  ||
		  (goal_const && rtx_equal_p (SET_SRC (pat), goal)
		   /* When looking for stack pointer + const,
		      make sure we don't use a stack adjust.  */
		   && !reg_overlap_mentioned_for_reload_p (SET_DEST (pat), goal)
		   && (valueno = true_regnum (valtry = SET_DEST (pat))) >= 0)
		  || (goal_mem
		      && (valueno = true_regnum (valtry = SET_DEST (pat))) >= 0
		      && rtx_renumbered_equal_p (goal, SET_SRC (pat)))
		  || (goal_mem
		      && (valueno = true_regnum (valtry = SET_SRC (pat))) >= 0
		      && rtx_renumbered_equal_p (goal, SET_DEST (pat)))
		  /* If we are looking for a constant,
		     and something equivalent to that constant was copied
		     into a reg, we can use that reg.  */
		  || (goal_const && REG_NOTES (p) != 0
		      && (tem = find_reg_note (p, REG_EQUIV, NULL_RTX))
		      && ((rtx_equal_p (XEXP (tem, 0), goal)
			   && (valueno
			       = true_regnum (valtry = SET_DEST (pat))) >= 0)
			  || (REG_P (SET_DEST (pat))
			      && GET_CODE (XEXP (tem, 0)) == CONST_DOUBLE
			      && SCALAR_FLOAT_MODE_P (GET_MODE (XEXP (tem, 0)))
			      && GET_CODE (goal) == CONST_INT
			      && 0 != (goaltry
				       = operand_subword (XEXP (tem, 0), 0, 0,
							  VOIDmode))
			      && rtx_equal_p (goal, goaltry)
			      && (valtry
				  = operand_subword (SET_DEST (pat), 0, 0,
						     VOIDmode))
			      && (valueno = true_regnum (valtry)) >= 0)))
		  || (goal_const && (tem = find_reg_note (p, REG_EQUIV,
							  NULL_RTX))
		      && REG_P (SET_DEST (pat))
		      && GET_CODE (XEXP (tem, 0)) == CONST_DOUBLE
		      && SCALAR_FLOAT_MODE_P (GET_MODE (XEXP (tem, 0)))
		      && GET_CODE (goal) == CONST_INT
		      && 0 != (goaltry = operand_subword (XEXP (tem, 0), 1, 0,
							  VOIDmode))
		      && rtx_equal_p (goal, goaltry)
		      && (valtry
			  = operand_subword (SET_DEST (pat), 1, 0, VOIDmode))
		      && (valueno = true_regnum (valtry)) >= 0)))
	    {
	      if (other >= 0)
		{
		  if (valueno != other)
		    continue;
		}
	      else if ((unsigned) valueno >= FIRST_PSEUDO_REGISTER)
		continue;
	      else
		{
		  int i;

		  for (i = hard_regno_nregs[valueno][mode] - 1; i >= 0; i--)
		    if (! TEST_HARD_REG_BIT (reg_class_contents[(int) class],
					     valueno + i))
		      break;
		  if (i >= 0)
		    continue;
		}
	      value = valtry;
	      where = p;
	      break;
	    }
	}
    }

  /* We found a previous insn copying GOAL into a suitable other reg VALUE
     (or copying VALUE into GOAL, if GOAL is also a register).
     Now verify that VALUE is really valid.  */

  /* VALUENO is the register number of VALUE; a hard register.  */

  /* Don't try to re-use something that is killed in this insn.  We want
     to be able to trust REG_UNUSED notes.  */
  if (REG_NOTES (where) != 0 && find_reg_note (where, REG_UNUSED, value))
    return 0;

  /* If we propose to get the value from the stack pointer or if GOAL is
     a MEM based on the stack pointer, we need a stable SP.  */
  if (valueno == STACK_POINTER_REGNUM || regno == STACK_POINTER_REGNUM
      || (goal_mem && reg_overlap_mentioned_for_reload_p (stack_pointer_rtx,
							  goal)))
    need_stable_sp = 1;

  /* Reject VALUE if the copy-insn moved the wrong sort of datum.  */
  if (GET_MODE (value) != mode)
    return 0;

  /* Reject VALUE if it was loaded from GOAL
     and is also a register that appears in the address of GOAL.  */

  if (goal_mem && value == SET_DEST (single_set (where))
      && refers_to_regno_for_reload_p (valueno,
				       (valueno
					+ hard_regno_nregs[valueno][mode]),
				       goal, (rtx*) 0))
    return 0;

  /* Reject registers that overlap GOAL.  */

  if (regno >= 0 && regno < FIRST_PSEUDO_REGISTER)
    nregs = hard_regno_nregs[regno][mode];
  else
    nregs = 1;
  valuenregs = hard_regno_nregs[valueno][mode];

  if (!goal_mem && !goal_const
      && regno + nregs > valueno && regno < valueno + valuenregs)
    return 0;

  /* Reject VALUE if it is one of the regs reserved for reloads.
     Reload1 knows how to reuse them anyway, and it would get
     confused if we allocated one without its knowledge.
     (Now that insns introduced by reload are ignored above,
     this case shouldn't happen, but I'm not positive.)  */

  if (reload_reg_p != 0 && reload_reg_p != (short *) (HOST_WIDE_INT) 1)
    {
      int i;
      for (i = 0; i < valuenregs; ++i)
	if (reload_reg_p[valueno + i] >= 0)
	  return 0;
    }

  /* Reject VALUE if it is a register being used for an input reload
     even if it is not one of those reserved.  */

  if (reload_reg_p != 0)
    {
      int i;
      for (i = 0; i < n_reloads; i++)
	if (rld[i].reg_rtx != 0 && rld[i].in)
	  {
	    int regno1 = REGNO (rld[i].reg_rtx);
	    int nregs1 = hard_regno_nregs[regno1]
					 [GET_MODE (rld[i].reg_rtx)];
	    if (regno1 < valueno + valuenregs
		&& regno1 + nregs1 > valueno)
	      return 0;
	  }
    }

  if (goal_mem)
    /* We must treat frame pointer as varying here,
       since it can vary--in a nonlocal goto as generated by expand_goto.  */
    goal_mem_addr_varies = !CONSTANT_ADDRESS_P (XEXP (goal, 0));

  /* Now verify that the values of GOAL and VALUE remain unaltered
     until INSN is reached.  */

  p = insn;
  while (1)
    {
      p = PREV_INSN (p);
      if (p == where)
	return value;

      /* Don't trust the conversion past a function call
	 if either of the two is in a call-clobbered register, or memory.  */
      if (CALL_P (p))
	{
	  int i;

	  if (goal_mem || need_stable_sp)
	    return 0;

	  if (regno >= 0 && regno < FIRST_PSEUDO_REGISTER)
	    for (i = 0; i < nregs; ++i)
	      if (call_used_regs[regno + i]
		  || HARD_REGNO_CALL_PART_CLOBBERED (regno + i, mode))
		return 0;

	  if (valueno >= 0 && valueno < FIRST_PSEUDO_REGISTER)
	    for (i = 0; i < valuenregs; ++i)
	      if (call_used_regs[valueno + i]
		  || HARD_REGNO_CALL_PART_CLOBBERED (valueno + i, mode))
		return 0;
	}

      if (INSN_P (p))
	{
	  pat = PATTERN (p);

	  /* Watch out for unspec_volatile, and volatile asms.  */
	  if (volatile_insn_p (pat))
	    return 0;

	  /* If this insn P stores in either GOAL or VALUE, return 0.
	     If GOAL is a memory ref and this insn writes memory, return 0.
	     If GOAL is a memory ref and its address is not constant,
	     and this insn P changes a register used in GOAL, return 0.  */

	  if (GET_CODE (pat) == COND_EXEC)
	    pat = COND_EXEC_CODE (pat);
	  if (GET_CODE (pat) == SET || GET_CODE (pat) == CLOBBER)
	    {
	      rtx dest = SET_DEST (pat);
	      while (GET_CODE (dest) == SUBREG
		     || GET_CODE (dest) == ZERO_EXTRACT
		     || GET_CODE (dest) == STRICT_LOW_PART)
		dest = XEXP (dest, 0);
	      if (REG_P (dest))
		{
		  int xregno = REGNO (dest);
		  int xnregs;
		  if (REGNO (dest) < FIRST_PSEUDO_REGISTER)
		    xnregs = hard_regno_nregs[xregno][GET_MODE (dest)];
		  else
		    xnregs = 1;
		  if (xregno < regno + nregs && xregno + xnregs > regno)
		    return 0;
		  if (xregno < valueno + valuenregs
		      && xregno + xnregs > valueno)
		    return 0;
		  if (goal_mem_addr_varies
		      && reg_overlap_mentioned_for_reload_p (dest, goal))
		    return 0;
		  if (xregno == STACK_POINTER_REGNUM && need_stable_sp)
		    return 0;
		}
	      else if (goal_mem && MEM_P (dest)
		       && ! push_operand (dest, GET_MODE (dest)))
		return 0;
	      else if (MEM_P (dest) && regno >= FIRST_PSEUDO_REGISTER
		       && reg_equiv_memory_loc[regno] != 0)
		return 0;
	      else if (need_stable_sp && push_operand (dest, GET_MODE (dest)))
		return 0;
	    }
	  else if (GET_CODE (pat) == PARALLEL)
	    {
	      int i;
	      for (i = XVECLEN (pat, 0) - 1; i >= 0; i--)
		{
		  rtx v1 = XVECEXP (pat, 0, i);
		  if (GET_CODE (v1) == COND_EXEC)
		    v1 = COND_EXEC_CODE (v1);
		  if (GET_CODE (v1) == SET || GET_CODE (v1) == CLOBBER)
		    {
		      rtx dest = SET_DEST (v1);
		      while (GET_CODE (dest) == SUBREG
			     || GET_CODE (dest) == ZERO_EXTRACT
			     || GET_CODE (dest) == STRICT_LOW_PART)
			dest = XEXP (dest, 0);
		      if (REG_P (dest))
			{
			  int xregno = REGNO (dest);
			  int xnregs;
			  if (REGNO (dest) < FIRST_PSEUDO_REGISTER)
			    xnregs = hard_regno_nregs[xregno][GET_MODE (dest)];
			  else
			    xnregs = 1;
			  if (xregno < regno + nregs
			      && xregno + xnregs > regno)
			    return 0;
			  if (xregno < valueno + valuenregs
			      && xregno + xnregs > valueno)
			    return 0;
			  if (goal_mem_addr_varies
			      && reg_overlap_mentioned_for_reload_p (dest,
								     goal))
			    return 0;
			  if (xregno == STACK_POINTER_REGNUM && need_stable_sp)
			    return 0;
			}
		      else if (goal_mem && MEM_P (dest)
			       && ! push_operand (dest, GET_MODE (dest)))
			return 0;
		      else if (MEM_P (dest) && regno >= FIRST_PSEUDO_REGISTER
			       && reg_equiv_memory_loc[regno] != 0)
			return 0;
		      else if (need_stable_sp
			       && push_operand (dest, GET_MODE (dest)))
			return 0;
		    }
		}
	    }

	  if (CALL_P (p) && CALL_INSN_FUNCTION_USAGE (p))
	    {
	      rtx link;

	      for (link = CALL_INSN_FUNCTION_USAGE (p); XEXP (link, 1) != 0;
		   link = XEXP (link, 1))
		{
		  pat = XEXP (link, 0);
		  if (GET_CODE (pat) == CLOBBER)
		    {
		      rtx dest = SET_DEST (pat);

		      if (REG_P (dest))
			{
			  int xregno = REGNO (dest);
			  int xnregs
			    = hard_regno_nregs[xregno][GET_MODE (dest)];

			  if (xregno < regno + nregs
			      && xregno + xnregs > regno)
			    return 0;
			  else if (xregno < valueno + valuenregs
				   && xregno + xnregs > valueno)
			    return 0;
			  else if (goal_mem_addr_varies
				   && reg_overlap_mentioned_for_reload_p (dest,
								     goal))
			    return 0;
			}

		      else if (goal_mem && MEM_P (dest)
			       && ! push_operand (dest, GET_MODE (dest)))
			return 0;
		      else if (need_stable_sp
			       && push_operand (dest, GET_MODE (dest)))
			return 0;
		    }
		}
	    }

#ifdef AUTO_INC_DEC
	  /* If this insn auto-increments or auto-decrements
	     either regno or valueno, return 0 now.
	     If GOAL is a memory ref and its address is not constant,
	     and this insn P increments a register used in GOAL, return 0.  */
	  {
	    rtx link;

	    for (link = REG_NOTES (p); link; link = XEXP (link, 1))
	      if (REG_NOTE_KIND (link) == REG_INC
		  && REG_P (XEXP (link, 0)))
		{
		  int incno = REGNO (XEXP (link, 0));
		  if (incno < regno + nregs && incno >= regno)
		    return 0;
		  if (incno < valueno + valuenregs && incno >= valueno)
		    return 0;
		  if (goal_mem_addr_varies
		      && reg_overlap_mentioned_for_reload_p (XEXP (link, 0),
							     goal))
		    return 0;
		}
	  }
#endif
	}
    }
}