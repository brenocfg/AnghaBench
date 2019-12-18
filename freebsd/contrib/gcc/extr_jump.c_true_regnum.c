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
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 scalar_t__* reg_renumber ; 
 scalar_t__ subreg_offset_representable_p (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int subreg_regno_offset (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
true_regnum (rtx x)
{
  if (REG_P (x))
    {
      if (REGNO (x) >= FIRST_PSEUDO_REGISTER && reg_renumber[REGNO (x)] >= 0)
	return reg_renumber[REGNO (x)];
      return REGNO (x);
    }
  if (GET_CODE (x) == SUBREG)
    {
      int base = true_regnum (SUBREG_REG (x));
      if (base >= 0
	  && base < FIRST_PSEUDO_REGISTER
	  && subreg_offset_representable_p (REGNO (SUBREG_REG (x)),
					    GET_MODE (SUBREG_REG (x)),
					    SUBREG_BYTE (x), GET_MODE (x)))
	return base + subreg_regno_offset (REGNO (SUBREG_REG (x)),
					   GET_MODE (SUBREG_REG (x)),
					   SUBREG_BYTE (x), GET_MODE (x));
    }
  return -1;
}