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

/* Variables and functions */
 unsigned int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 size_t GET_MODE (scalar_t__) ; 
 scalar_t__ PARALLEL ; 
 unsigned int REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ SET ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ZERO_EXTRACT ; 
 unsigned int** hard_regno_nregs ; 

__attribute__((used)) static int
reg_bitfield_target_p (rtx x, rtx body)
{
  int i;

  if (GET_CODE (body) == SET)
    {
      rtx dest = SET_DEST (body);
      rtx target;
      unsigned int regno, tregno, endregno, endtregno;

      if (GET_CODE (dest) == ZERO_EXTRACT)
	target = XEXP (dest, 0);
      else if (GET_CODE (dest) == STRICT_LOW_PART)
	target = SUBREG_REG (XEXP (dest, 0));
      else
	return 0;

      if (GET_CODE (target) == SUBREG)
	target = SUBREG_REG (target);

      if (!REG_P (target))
	return 0;

      tregno = REGNO (target), regno = REGNO (x);
      if (tregno >= FIRST_PSEUDO_REGISTER || regno >= FIRST_PSEUDO_REGISTER)
	return target == x;

      endtregno = tregno + hard_regno_nregs[tregno][GET_MODE (target)];
      endregno = regno + hard_regno_nregs[regno][GET_MODE (x)];

      return endregno > tregno && regno < endtregno;
    }

  else if (GET_CODE (body) == PARALLEL)
    for (i = XVECLEN (body, 0) - 1; i >= 0; i--)
      if (reg_bitfield_target_p (x, XVECEXP (body, 0, i)))
	return 1;

  return 0;
}