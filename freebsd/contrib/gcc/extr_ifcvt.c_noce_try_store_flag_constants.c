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
struct noce_if_info {int /*<<< orphan*/  insn_a; int /*<<< orphan*/  jump; scalar_t__ x; int /*<<< orphan*/  cond; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  AND ; 
 int /*<<< orphan*/  ASHIFT ; 
 int BRANCH_COST ; 
 scalar_t__ CONST_INT ; 
 int FALSE ; 
 scalar_t__ GEN_INT (scalar_t__) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  INSN_LOCATOR (int /*<<< orphan*/ ) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOR ; 
 int /*<<< orphan*/  MINUS ; 
 int /*<<< orphan*/  OPTAB_WIDEN ; 
 int /*<<< orphan*/  PLUS ; 
 scalar_t__ STORE_FLAG_VALUE ; 
 int TRUE ; 
 scalar_t__ UNKNOWN ; 
 int /*<<< orphan*/  emit_insn_before_setloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ end_ifcvt_sequence (struct noce_if_info*) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ exact_log2 (scalar_t__) ; 
 scalar_t__ expand_simple_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_new_pseudos ; 
 int /*<<< orphan*/  noce_emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ noce_emit_store_flag (struct noce_if_info*,scalar_t__,int,int) ; 
 scalar_t__ reversed_comparison_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 
 scalar_t__ trunc_int_for_mode (scalar_t__,int) ; 

__attribute__((used)) static int
noce_try_store_flag_constants (struct noce_if_info *if_info)
{
  rtx target, seq;
  int reversep;
  HOST_WIDE_INT itrue, ifalse, diff, tmp;
  int normalize, can_reverse;
  enum machine_mode mode;

  if (! no_new_pseudos
      && GET_CODE (if_info->a) == CONST_INT
      && GET_CODE (if_info->b) == CONST_INT)
    {
      mode = GET_MODE (if_info->x);
      ifalse = INTVAL (if_info->a);
      itrue = INTVAL (if_info->b);

      /* Make sure we can represent the difference between the two values.  */
      if ((itrue - ifalse > 0)
	  != ((ifalse < 0) != (itrue < 0) ? ifalse < 0 : ifalse < itrue))
	return FALSE;

      diff = trunc_int_for_mode (itrue - ifalse, mode);

      can_reverse = (reversed_comparison_code (if_info->cond, if_info->jump)
		     != UNKNOWN);

      reversep = 0;
      if (diff == STORE_FLAG_VALUE || diff == -STORE_FLAG_VALUE)
	normalize = 0;
      else if (ifalse == 0 && exact_log2 (itrue) >= 0
	       && (STORE_FLAG_VALUE == 1
		   || BRANCH_COST >= 2))
	normalize = 1;
      else if (itrue == 0 && exact_log2 (ifalse) >= 0 && can_reverse
	       && (STORE_FLAG_VALUE == 1 || BRANCH_COST >= 2))
	normalize = 1, reversep = 1;
      else if (itrue == -1
	       && (STORE_FLAG_VALUE == -1
		   || BRANCH_COST >= 2))
	normalize = -1;
      else if (ifalse == -1 && can_reverse
	       && (STORE_FLAG_VALUE == -1 || BRANCH_COST >= 2))
	normalize = -1, reversep = 1;
      else if ((BRANCH_COST >= 2 && STORE_FLAG_VALUE == -1)
	       || BRANCH_COST >= 3)
	normalize = -1;
      else
	return FALSE;

      if (reversep)
	{
	  tmp = itrue; itrue = ifalse; ifalse = tmp;
	  diff = trunc_int_for_mode (-diff, mode);
	}

      start_sequence ();
      target = noce_emit_store_flag (if_info, if_info->x, reversep, normalize);
      if (! target)
	{
	  end_sequence ();
	  return FALSE;
	}

      /* if (test) x = 3; else x = 4;
	 =>   x = 3 + (test == 0);  */
      if (diff == STORE_FLAG_VALUE || diff == -STORE_FLAG_VALUE)
	{
	  target = expand_simple_binop (mode,
					(diff == STORE_FLAG_VALUE
					 ? PLUS : MINUS),
					GEN_INT (ifalse), target, if_info->x, 0,
					OPTAB_WIDEN);
	}

      /* if (test) x = 8; else x = 0;
	 =>   x = (test != 0) << 3;  */
      else if (ifalse == 0 && (tmp = exact_log2 (itrue)) >= 0)
	{
	  target = expand_simple_binop (mode, ASHIFT,
					target, GEN_INT (tmp), if_info->x, 0,
					OPTAB_WIDEN);
	}

      /* if (test) x = -1; else x = b;
	 =>   x = -(test != 0) | b;  */
      else if (itrue == -1)
	{
	  target = expand_simple_binop (mode, IOR,
					target, GEN_INT (ifalse), if_info->x, 0,
					OPTAB_WIDEN);
	}

      /* if (test) x = a; else x = b;
	 =>   x = (-(test != 0) & (b - a)) + a;  */
      else
	{
	  target = expand_simple_binop (mode, AND,
					target, GEN_INT (diff), if_info->x, 0,
					OPTAB_WIDEN);
	  if (target)
	    target = expand_simple_binop (mode, PLUS,
					  target, GEN_INT (ifalse),
					  if_info->x, 0, OPTAB_WIDEN);
	}

      if (! target)
	{
	  end_sequence ();
	  return FALSE;
	}

      if (target != if_info->x)
	noce_emit_move_insn (if_info->x, target);

      seq = end_ifcvt_sequence (if_info);
      if (!seq)
	return FALSE;

      emit_insn_before_setloc (seq, if_info->jump,
			       INSN_LOCATOR (if_info->insn_a));
      return TRUE;
    }

  return FALSE;
}