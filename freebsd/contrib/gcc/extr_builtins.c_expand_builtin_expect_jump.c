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
typedef  int /*<<< orphan*/  tree ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 int /*<<< orphan*/  LABEL_P (scalar_t__) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NOTE_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PRED_BUILTIN_EXPECT ; 
 scalar_t__ SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ any_condjump_p (scalar_t__) ; 
 scalar_t__ any_uncondjump_p (scalar_t__) ; 
 int /*<<< orphan*/  do_jump (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ get_insns () ; 
 scalar_t__ get_last_insn () ; 
 scalar_t__ integer_onep (int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 
 scalar_t__ next_nonnote_insn (scalar_t__) ; 
 scalar_t__ pc_rtx ; 
 int /*<<< orphan*/  pc_set (scalar_t__) ; 
 int /*<<< orphan*/  predict_insn_def (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ prev_nonnote_insn (scalar_t__) ; 
 int /*<<< orphan*/  start_sequence () ; 

rtx
expand_builtin_expect_jump (tree exp, rtx if_false_label, rtx if_true_label)
{
  tree arglist = TREE_OPERAND (exp, 1);
  tree arg0 = TREE_VALUE (arglist);
  tree arg1 = TREE_VALUE (TREE_CHAIN (arglist));
  rtx ret = NULL_RTX;

  /* Only handle __builtin_expect (test, 0) and
     __builtin_expect (test, 1).  */
  if (TREE_CODE (TREE_TYPE (arg1)) == INTEGER_TYPE
      && (integer_zerop (arg1) || integer_onep (arg1)))
    {
      rtx insn, drop_through_label, temp;

      /* Expand the jump insns.  */
      start_sequence ();
      do_jump (arg0, if_false_label, if_true_label);
      ret = get_insns ();

      drop_through_label = get_last_insn ();
      if (drop_through_label && NOTE_P (drop_through_label))
	drop_through_label = prev_nonnote_insn (drop_through_label);
      if (drop_through_label && !LABEL_P (drop_through_label))
	drop_through_label = NULL_RTX;
      end_sequence ();

      if (! if_true_label)
	if_true_label = drop_through_label;
      if (! if_false_label)
	if_false_label = drop_through_label;

      /* Go through and add the expect's to each of the conditional jumps.  */
      insn = ret;
      while (insn != NULL_RTX)
	{
	  rtx next = NEXT_INSN (insn);

	  if (JUMP_P (insn) && any_condjump_p (insn))
	    {
	      rtx ifelse = SET_SRC (pc_set (insn));
	      rtx then_dest = XEXP (ifelse, 1);
	      rtx else_dest = XEXP (ifelse, 2);
	      int taken = -1;

	      /* First check if we recognize any of the labels.  */
	      if (GET_CODE (then_dest) == LABEL_REF
		  && XEXP (then_dest, 0) == if_true_label)
		taken = 1;
	      else if (GET_CODE (then_dest) == LABEL_REF
		       && XEXP (then_dest, 0) == if_false_label)
		taken = 0;
	      else if (GET_CODE (else_dest) == LABEL_REF
		       && XEXP (else_dest, 0) == if_false_label)
		taken = 1;
	      else if (GET_CODE (else_dest) == LABEL_REF
		       && XEXP (else_dest, 0) == if_true_label)
		taken = 0;
	      /* Otherwise check where we drop through.  */
	      else if (else_dest == pc_rtx)
		{
		  if (next && NOTE_P (next))
		    next = next_nonnote_insn (next);

		  if (next && JUMP_P (next)
		      && any_uncondjump_p (next))
		    temp = XEXP (SET_SRC (pc_set (next)), 0);
		  else
		    temp = next;

		  /* TEMP is either a CODE_LABEL, NULL_RTX or something
		     else that can't possibly match either target label.  */
		  if (temp == if_false_label)
		    taken = 1;
		  else if (temp == if_true_label)
		    taken = 0;
		}
	      else if (then_dest == pc_rtx)
		{
		  if (next && NOTE_P (next))
		    next = next_nonnote_insn (next);

		  if (next && JUMP_P (next)
		      && any_uncondjump_p (next))
		    temp = XEXP (SET_SRC (pc_set (next)), 0);
		  else
		    temp = next;

		  if (temp == if_false_label)
		    taken = 0;
		  else if (temp == if_true_label)
		    taken = 1;
		}

	      if (taken != -1)
		{
		  /* If the test is expected to fail, reverse the
		     probabilities.  */
		  if (integer_zerop (arg1))
		    taken = 1 - taken;
		  predict_insn_def (insn, PRED_BUILTIN_EXPECT, taken);
		}
	    }

	  insn = next;
	}
    }

  return ret;
}