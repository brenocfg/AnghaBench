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
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ NOOP_MOVE_INSN_CODE ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 int /*<<< orphan*/  REG_RETVAL ; 
 scalar_t__ SET ; 
 scalar_t__ USE ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ set_noop_p (int /*<<< orphan*/ ) ; 

int
noop_move_p (rtx insn)
{
  rtx pat = PATTERN (insn);

  if (INSN_CODE (insn) == NOOP_MOVE_INSN_CODE)
    return 1;

  /* Insns carrying these notes are useful later on.  */
  if (find_reg_note (insn, REG_EQUAL, NULL_RTX))
    return 0;

  /* For now treat an insn with a REG_RETVAL note as a
     a special insn which should not be considered a no-op.  */
  if (find_reg_note (insn, REG_RETVAL, NULL_RTX))
    return 0;

  if (GET_CODE (pat) == SET && set_noop_p (pat))
    return 1;

  if (GET_CODE (pat) == PARALLEL)
    {
      int i;
      /* If nothing but SETs of registers to themselves,
	 this insn can also be deleted.  */
      for (i = 0; i < XVECLEN (pat, 0); i++)
	{
	  rtx tem = XVECEXP (pat, 0, i);

	  if (GET_CODE (tem) == USE
	      || GET_CODE (tem) == CLOBBER)
	    continue;

	  if (GET_CODE (tem) != SET || ! set_noop_p (tem))
	    return 0;
	}

      return 1;
    }
  return 0;
}