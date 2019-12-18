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
 scalar_t__ FIRST_STACK_REG ; 
 scalar_t__ FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_CUID (int /*<<< orphan*/ ) ; 
 scalar_t__ JUMP_P (int /*<<< orphan*/ ) ; 
 scalar_t__ LAST_STACK_REG ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ can_copy_p (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_float_store ; 
 scalar_t__ general_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_expr_in_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_killed_in_block_p (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ oprs_unchanged_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ set_noop_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hash_scan_set (rtx insn)
{
  rtx pat = PATTERN (insn);
  rtx src = SET_SRC (pat);
  rtx dest = SET_DEST (pat);

  /* We are only interested in loads and stores.  */
  if (! MEM_P (src) && ! MEM_P (dest))
    return;

  /* Don't mess with jumps and nops.  */
  if (JUMP_P (insn) || set_noop_p (pat))
    return;

  if (REG_P (dest))
    {
      if (/* Don't CSE something if we can't do a reg/reg copy.  */
	  can_copy_p (GET_MODE (dest))
	  /* Is SET_SRC something we want to gcse?  */
	  && general_operand (src, GET_MODE (src))
#ifdef STACK_REGS
	  /* Never consider insns touching the register stack.  It may
	     create situations that reg-stack cannot handle (e.g. a stack
	     register live across an abnormal edge).  */
	  && (REGNO (dest) < FIRST_STACK_REG || REGNO (dest) > LAST_STACK_REG)
#endif
	  /* An expression is not available if its operands are
	     subsequently modified, including this insn.  */
	  && oprs_unchanged_p (src, insn, true))
	{
	  insert_expr_in_table (src, insn);
	}
    }
  else if (REG_P (src))
    {
      /* Only record sets of pseudo-regs in the hash table.  */
      if (/* Don't CSE something if we can't do a reg/reg copy.  */
	  can_copy_p (GET_MODE (src))
	  /* Is SET_DEST something we want to gcse?  */
	  && general_operand (dest, GET_MODE (dest))
#ifdef STACK_REGS
	  /* As above for STACK_REGS.  */
	  && (REGNO (src) < FIRST_STACK_REG || REGNO (src) > LAST_STACK_REG)
#endif
	  && ! (flag_float_store && FLOAT_MODE_P (GET_MODE (dest)))
	  /* Check if the memory expression is killed after insn.  */
	  && ! load_killed_in_block_p (INSN_CUID (insn) + 1, dest, true)
	  && oprs_unchanged_p (XEXP (dest, 0), insn, true))
	{
	  insert_expr_in_table (dest, insn);
	}
    }
}