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
typedef  int /*<<< orphan*/  regset ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_REGNO_REG_SET (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int REGNO_REG_SET_P (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SET_REGNO_REG_SET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int** hard_regno_nregs ; 
 int /*<<< orphan*/  reload_completed ; 

__attribute__((used)) static int
assign_reg_reg_set (regset set, rtx reg, int value)
{
  unsigned regno = REGNO (reg);
  int nregs, i, old;

  if (regno >= FIRST_PSEUDO_REGISTER)
    {
      gcc_assert (!reload_completed);
      nregs = 1;
    }
  else
    nregs = hard_regno_nregs[regno][GET_MODE (reg)];
  for (old = 0, i = nregs; --i >= 0; regno++)
    {
      if ((value != 0) == REGNO_REG_SET_P (set, regno))
	continue;
      if (value)
	old++, SET_REGNO_REG_SET (set, regno);
      else
	old--, CLEAR_REGNO_REG_SET (set, regno);
    }
  return old;
}