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
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const2_rtx ; 
 int /*<<< orphan*/  gen_add3_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pc_rtx ; 
 int /*<<< orphan*/  word_mode ; 

__attribute__((used)) static rtx
discover_flags_reg (void)
{
  rtx tmp;
  tmp = gen_rtx_REG (word_mode, 10000);
  tmp = gen_add3_insn (tmp, tmp, const2_rtx);

  /* If we get something that isn't a simple set, or a
     [(set ..) (clobber ..)], this whole function will go wrong.  */
  if (GET_CODE (tmp) == SET)
    return NULL_RTX;
  else if (GET_CODE (tmp) == PARALLEL)
    {
      int found;

      if (XVECLEN (tmp, 0) != 2)
	return pc_rtx;
      tmp = XVECEXP (tmp, 0, 1);
      if (GET_CODE (tmp) != CLOBBER)
	return pc_rtx;
      tmp = XEXP (tmp, 0);

      /* Don't do anything foolish if the md wanted to clobber a
	 scratch or something.  We only care about hard regs.
	 Moreover we don't like the notion of subregs of hard regs.  */
      if (GET_CODE (tmp) == SUBREG
	  && REG_P (SUBREG_REG (tmp))
	  && REGNO (SUBREG_REG (tmp)) < FIRST_PSEUDO_REGISTER)
	return pc_rtx;
      found = (REG_P (tmp) && REGNO (tmp) < FIRST_PSEUDO_REGISTER);

      return (found ? tmp : NULL_RTX);
    }

  return pc_rtx;
}