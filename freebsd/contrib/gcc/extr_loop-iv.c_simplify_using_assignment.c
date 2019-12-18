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
typedef  int /*<<< orphan*/  regset ;

/* Variables and functions */
 scalar_t__ CALL_P (scalar_t__) ; 
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 int /*<<< orphan*/  SET_REGNO_REG_SET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ altered_reg_used (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_reg_equal_equiv_note (scalar_t__) ; 
 scalar_t__ for_each_rtx (scalar_t__*,scalar_t__ (*) (scalar_t__*,int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_altered ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regs_invalidated_by_call ; 
 int /*<<< orphan*/  simple_rhs_p (scalar_t__) ; 
 scalar_t__ simplify_replace_rtx (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 

__attribute__((used)) static void
simplify_using_assignment (rtx insn, rtx *expr, regset altered)
{
  rtx set = single_set (insn);
  rtx lhs = NULL_RTX, rhs;
  bool ret = false;

  if (set)
    {
      lhs = SET_DEST (set);
      if (!REG_P (lhs)
	  || altered_reg_used (&lhs, altered))
	ret = true;
    }
  else
    ret = true;

  note_stores (PATTERN (insn), mark_altered, altered);
  if (CALL_P (insn))
    {
      int i;

      /* Kill all call clobbered registers.  */
      for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
	if (TEST_HARD_REG_BIT (regs_invalidated_by_call, i))
	  SET_REGNO_REG_SET (altered, i);
    }

  if (ret)
    return;

  rhs = find_reg_equal_equiv_note (insn);
  if (rhs)
    rhs = XEXP (rhs, 0);
  else
    rhs = SET_SRC (set);

  if (!simple_rhs_p (rhs))
    return;

  if (for_each_rtx (&rhs, altered_reg_used, altered))
    return;

  *expr = simplify_replace_rtx (*expr, lhs, rhs);
}