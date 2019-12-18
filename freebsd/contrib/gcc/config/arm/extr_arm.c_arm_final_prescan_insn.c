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
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 int AND ; 
 int /*<<< orphan*/  ARM_INVERSE_CONDITION_CODE (int /*<<< orphan*/ ) ; 
#define  BARRIER 133 
#define  CALL_INSN 132 
 int /*<<< orphan*/  CIRRUS_NOT ; 
 int CLOBBER ; 
#define  CODE_LABEL 131 
 scalar_t__ CODE_LABEL_NUMBER (int /*<<< orphan*/ *) ; 
 scalar_t__ CONDS_JUMP_CLOB ; 
#define  CONDS_NOCOND 130 
 int FALSE ; 
 int GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ IF_THEN_ELSE ; 
#define  INSN 129 
#define  JUMP_INSN 128 
 int LABEL_NUSES (int /*<<< orphan*/ *) ; 
 int LABEL_REF ; 
 int NE ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/ * PATTERN (int /*<<< orphan*/ *) ; 
 scalar_t__ PC ; 
 scalar_t__ RETURN ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/ * SET_DEST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SET_SRC (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int USE ; 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * XVECEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XVECLEN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_arch5 ; 
 int arm_ccfsm_state ; 
 int /*<<< orphan*/  arm_current_cc ; 
 int /*<<< orphan*/ * arm_target_insn ; 
 scalar_t__ arm_target_label ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_arm_condition_code (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_attr_cirrus (int /*<<< orphan*/ *) ; 
 int const get_attr_conds (int /*<<< orphan*/ *) ; 
 int max_insns_skipped ; 
 int /*<<< orphan*/ * next_nonnote_insn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optimize_size ; 
 int /*<<< orphan*/  recog (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ simplejump_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_return_insn (int,int /*<<< orphan*/ *) ; 

void
arm_final_prescan_insn (rtx insn)
{
  /* BODY will hold the body of INSN.  */
  rtx body = PATTERN (insn);

  /* This will be 1 if trying to repeat the trick, and things need to be
     reversed if it appears to fail.  */
  int reverse = 0;

  /* JUMP_CLOBBERS will be one implies that the conditions if a branch is
     taken are clobbered, even if the rtl suggests otherwise.  It also
     means that we have to grub around within the jump expression to find
     out what the conditions are when the jump isn't taken.  */
  int jump_clobbers = 0;

  /* If we start with a return insn, we only succeed if we find another one.  */
  int seeking_return = 0;

  /* START_INSN will hold the insn from where we start looking.  This is the
     first insn after the following code_label if REVERSE is true.  */
  rtx start_insn = insn;

  /* If in state 4, check if the target branch is reached, in order to
     change back to state 0.  */
  if (arm_ccfsm_state == 4)
    {
      if (insn == arm_target_insn)
	{
	  arm_target_insn = NULL;
	  arm_ccfsm_state = 0;
	}
      return;
    }

  /* If in state 3, it is possible to repeat the trick, if this insn is an
     unconditional branch to a label, and immediately following this branch
     is the previous target label which is only used once, and the label this
     branch jumps to is not too far off.  */
  if (arm_ccfsm_state == 3)
    {
      if (simplejump_p (insn))
	{
	  start_insn = next_nonnote_insn (start_insn);
	  if (GET_CODE (start_insn) == BARRIER)
	    {
	      /* XXX Isn't this always a barrier?  */
	      start_insn = next_nonnote_insn (start_insn);
	    }
	  if (GET_CODE (start_insn) == CODE_LABEL
	      && CODE_LABEL_NUMBER (start_insn) == arm_target_label
	      && LABEL_NUSES (start_insn) == 1)
	    reverse = TRUE;
	  else
	    return;
	}
      else if (GET_CODE (body) == RETURN)
        {
	  start_insn = next_nonnote_insn (start_insn);
	  if (GET_CODE (start_insn) == BARRIER)
	    start_insn = next_nonnote_insn (start_insn);
	  if (GET_CODE (start_insn) == CODE_LABEL
	      && CODE_LABEL_NUMBER (start_insn) == arm_target_label
	      && LABEL_NUSES (start_insn) == 1)
	    {
	      reverse = TRUE;
	      seeking_return = 1;
	    }
	  else
	    return;
        }
      else
	return;
    }

  gcc_assert (!arm_ccfsm_state || reverse);
  if (GET_CODE (insn) != JUMP_INSN)
    return;

  /* This jump might be paralleled with a clobber of the condition codes
     the jump should always come first */
  if (GET_CODE (body) == PARALLEL && XVECLEN (body, 0) > 0)
    body = XVECEXP (body, 0, 0);

  if (reverse
      || (GET_CODE (body) == SET && GET_CODE (SET_DEST (body)) == PC
	  && GET_CODE (SET_SRC (body)) == IF_THEN_ELSE))
    {
      int insns_skipped;
      int fail = FALSE, succeed = FALSE;
      /* Flag which part of the IF_THEN_ELSE is the LABEL_REF.  */
      int then_not_else = TRUE;
      rtx this_insn = start_insn, label = 0;

      /* If the jump cannot be done with one instruction, we cannot
	 conditionally execute the instruction in the inverse case.  */
      if (get_attr_conds (insn) == CONDS_JUMP_CLOB)
	{
	  jump_clobbers = 1;
	  return;
	}

      /* Register the insn jumped to.  */
      if (reverse)
        {
	  if (!seeking_return)
	    label = XEXP (SET_SRC (body), 0);
        }
      else if (GET_CODE (XEXP (SET_SRC (body), 1)) == LABEL_REF)
	label = XEXP (XEXP (SET_SRC (body), 1), 0);
      else if (GET_CODE (XEXP (SET_SRC (body), 2)) == LABEL_REF)
	{
	  label = XEXP (XEXP (SET_SRC (body), 2), 0);
	  then_not_else = FALSE;
	}
      else if (GET_CODE (XEXP (SET_SRC (body), 1)) == RETURN)
	seeking_return = 1;
      else if (GET_CODE (XEXP (SET_SRC (body), 2)) == RETURN)
        {
	  seeking_return = 1;
	  then_not_else = FALSE;
        }
      else
	gcc_unreachable ();

      /* See how many insns this branch skips, and what kind of insns.  If all
	 insns are okay, and the label or unconditional branch to the same
	 label is not too far away, succeed.  */
      for (insns_skipped = 0;
	   !fail && !succeed && insns_skipped++ < max_insns_skipped;)
	{
	  rtx scanbody;

	  this_insn = next_nonnote_insn (this_insn);
	  if (!this_insn)
	    break;

	  switch (GET_CODE (this_insn))
	    {
	    case CODE_LABEL:
	      /* Succeed if it is the target label, otherwise fail since
		 control falls in from somewhere else.  */
	      if (this_insn == label)
		{
		  if (jump_clobbers)
		    {
		      arm_ccfsm_state = 2;
		      this_insn = next_nonnote_insn (this_insn);
		    }
		  else
		    arm_ccfsm_state = 1;
		  succeed = TRUE;
		}
	      else
		fail = TRUE;
	      break;

	    case BARRIER:
	      /* Succeed if the following insn is the target label.
		 Otherwise fail.
		 If return insns are used then the last insn in a function
		 will be a barrier.  */
	      this_insn = next_nonnote_insn (this_insn);
	      if (this_insn && this_insn == label)
		{
		  if (jump_clobbers)
		    {
		      arm_ccfsm_state = 2;
		      this_insn = next_nonnote_insn (this_insn);
		    }
		  else
		    arm_ccfsm_state = 1;
		  succeed = TRUE;
		}
	      else
		fail = TRUE;
	      break;

	    case CALL_INSN:
	      /* The AAPCS says that conditional calls should not be
		 used since they make interworking inefficient (the
		 linker can't transform BL<cond> into BLX).  That's
		 only a problem if the machine has BLX.  */
	      if (arm_arch5)
		{
		  fail = TRUE;
		  break;
		}

	      /* Succeed if the following insn is the target label, or
		 if the following two insns are a barrier and the
		 target label.  */
	      this_insn = next_nonnote_insn (this_insn);
	      if (this_insn && GET_CODE (this_insn) == BARRIER)
		this_insn = next_nonnote_insn (this_insn);

	      if (this_insn && this_insn == label
		  && insns_skipped < max_insns_skipped)
		{
		  if (jump_clobbers)
		    {
		      arm_ccfsm_state = 2;
		      this_insn = next_nonnote_insn (this_insn);
		    }
		  else
		    arm_ccfsm_state = 1;
		  succeed = TRUE;
		}
	      else
		fail = TRUE;
	      break;

	    case JUMP_INSN:
      	      /* If this is an unconditional branch to the same label, succeed.
		 If it is to another label, do nothing.  If it is conditional,
		 fail.  */
	      /* XXX Probably, the tests for SET and the PC are
		 unnecessary.  */

	      scanbody = PATTERN (this_insn);
	      if (GET_CODE (scanbody) == SET
		  && GET_CODE (SET_DEST (scanbody)) == PC)
		{
		  if (GET_CODE (SET_SRC (scanbody)) == LABEL_REF
		      && XEXP (SET_SRC (scanbody), 0) == label && !reverse)
		    {
		      arm_ccfsm_state = 2;
		      succeed = TRUE;
		    }
		  else if (GET_CODE (SET_SRC (scanbody)) == IF_THEN_ELSE)
		    fail = TRUE;
		}
	      /* Fail if a conditional return is undesirable (e.g. on a
		 StrongARM), but still allow this if optimizing for size.  */
	      else if (GET_CODE (scanbody) == RETURN
		       && !use_return_insn (TRUE, NULL)
		       && !optimize_size)
		fail = TRUE;
	      else if (GET_CODE (scanbody) == RETURN
		       && seeking_return)
	        {
		  arm_ccfsm_state = 2;
		  succeed = TRUE;
	        }
	      else if (GET_CODE (scanbody) == PARALLEL)
	        {
		  switch (get_attr_conds (this_insn))
		    {
		    case CONDS_NOCOND:
		      break;
		    default:
		      fail = TRUE;
		      break;
		    }
		}
	      else
		fail = TRUE;	/* Unrecognized jump (e.g. epilogue).  */

	      break;

	    case INSN:
	      /* Instructions using or affecting the condition codes make it
		 fail.  */
	      scanbody = PATTERN (this_insn);
	      if (!(GET_CODE (scanbody) == SET
		    || GET_CODE (scanbody) == PARALLEL)
		  || get_attr_conds (this_insn) != CONDS_NOCOND)
		fail = TRUE;

	      /* A conditional cirrus instruction must be followed by
		 a non Cirrus instruction.  However, since we
		 conditionalize instructions in this function and by
		 the time we get here we can't add instructions
		 (nops), because shorten_branches() has already been
		 called, we will disable conditionalizing Cirrus
		 instructions to be safe.  */
	      if (GET_CODE (scanbody) != USE
		  && GET_CODE (scanbody) != CLOBBER
		  && get_attr_cirrus (this_insn) != CIRRUS_NOT)
		fail = TRUE;
	      break;

	    default:
	      break;
	    }
	}
      if (succeed)
	{
	  if ((!seeking_return) && (arm_ccfsm_state == 1 || reverse))
	    arm_target_label = CODE_LABEL_NUMBER (label);
	  else
	    {
	      gcc_assert (seeking_return || arm_ccfsm_state == 2);

	      while (this_insn && GET_CODE (PATTERN (this_insn)) == USE)
	        {
		  this_insn = next_nonnote_insn (this_insn);
		  gcc_assert (!this_insn
			      || (GET_CODE (this_insn) != BARRIER
				  && GET_CODE (this_insn) != CODE_LABEL));
	        }
	      if (!this_insn)
	        {
		  /* Oh, dear! we ran off the end.. give up.  */
		  recog (PATTERN (insn), insn, NULL);
		  arm_ccfsm_state = 0;
		  arm_target_insn = NULL;
		  return;
	        }
	      arm_target_insn = this_insn;
	    }
	  if (jump_clobbers)
	    {
	      gcc_assert (!reverse);
	      arm_current_cc =
		  get_arm_condition_code (XEXP (XEXP (XEXP (SET_SRC (body),
							    0), 0), 1));
	      if (GET_CODE (XEXP (XEXP (SET_SRC (body), 0), 0)) == AND)
		arm_current_cc = ARM_INVERSE_CONDITION_CODE (arm_current_cc);
	      if (GET_CODE (XEXP (SET_SRC (body), 0)) == NE)
		arm_current_cc = ARM_INVERSE_CONDITION_CODE (arm_current_cc);
	    }
	  else
	    {
	      /* If REVERSE is true, ARM_CURRENT_CC needs to be inverted from
		 what it was.  */
	      if (!reverse)
		arm_current_cc = get_arm_condition_code (XEXP (SET_SRC (body),
							       0));
	    }

	  if (reverse || then_not_else)
	    arm_current_cc = ARM_INVERSE_CONDITION_CODE (arm_current_cc);
	}

      /* Restore recog_data (getting the attributes of other insns can
	 destroy this array, but final.c assumes that it remains intact
	 across this call; since the insn has been recognized already we
	 call recog direct).  */
      recog (PATTERN (insn), insn, NULL);
    }
}