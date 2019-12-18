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
struct noce_if_info {scalar_t__ a; scalar_t__ b; int /*<<< orphan*/  insn_a; int /*<<< orphan*/  jump; scalar_t__ x; int /*<<< orphan*/  cond; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  AND ; 
 int BRANCH_COST ; 
 int FALSE ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  INSN_LOCATOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPTAB_WIDEN ; 
 int STORE_FLAG_VALUE ; 
 int TRUE ; 
 scalar_t__ UNKNOWN ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  emit_insn_before_setloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ end_ifcvt_sequence (struct noce_if_info*) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ expand_simple_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_new_pseudos ; 
 int /*<<< orphan*/  noce_emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ noce_emit_store_flag (struct noce_if_info*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ reversed_comparison_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static int
noce_try_store_flag_mask (struct noce_if_info *if_info)
{
  rtx target, seq;
  int reversep;

  reversep = 0;
  if (! no_new_pseudos
      && (BRANCH_COST >= 2
	  || STORE_FLAG_VALUE == -1)
      && ((if_info->a == const0_rtx
	   && rtx_equal_p (if_info->b, if_info->x))
	  || ((reversep = (reversed_comparison_code (if_info->cond,
						     if_info->jump)
			   != UNKNOWN))
	      && if_info->b == const0_rtx
	      && rtx_equal_p (if_info->a, if_info->x))))
    {
      start_sequence ();
      target = noce_emit_store_flag (if_info,
				     gen_reg_rtx (GET_MODE (if_info->x)),
				     reversep, -1);
      if (target)
        target = expand_simple_binop (GET_MODE (if_info->x), AND,
				      if_info->x,
				      target, if_info->x, 0,
				      OPTAB_WIDEN);

      if (target)
	{
	  if (target != if_info->x)
	    noce_emit_move_insn (if_info->x, target);

	  seq = end_ifcvt_sequence (if_info);
	  if (!seq)
	    return FALSE;

	  emit_insn_before_setloc (seq, if_info->jump,
				   INSN_LOCATOR (if_info->insn_a));
	  return TRUE;
	}

      end_sequence ();
    }

  return FALSE;
}