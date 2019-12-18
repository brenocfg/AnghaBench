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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_jump ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insn_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_cmp_insn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ swap_commutative_operands_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int swap_condition (int) ; 
 int unsigned_condition (int) ; 

void
emit_cmp_and_jump_insns (rtx x, rtx y, enum rtx_code comparison, rtx size,
			 enum machine_mode mode, int unsignedp, rtx label)
{
  rtx op0 = x, op1 = y;

  /* Swap operands and condition to ensure canonical RTL.  */
  if (swap_commutative_operands_p (x, y))
    {
      /* If we're not emitting a branch, this means some caller
         is out of sync.  */
      gcc_assert (label);

      op0 = y, op1 = x;
      comparison = swap_condition (comparison);
    }

#ifdef HAVE_cc0
  /* If OP0 is still a constant, then both X and Y must be constants.
     Force X into a register to create canonical RTL.  */
  if (CONSTANT_P (op0))
    op0 = force_reg (mode, op0);
#endif

  if (unsignedp)
    comparison = unsigned_condition (comparison);

  prepare_cmp_insn (&op0, &op1, &comparison, size, &mode, &unsignedp,
		    ccp_jump);
  emit_cmp_and_jump_insn_1 (op0, op1, mode, comparison, unsignedp, label);
}