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
 size_t BLKmode ; 
 int FIRST_PSEUDO_REGISTER ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REGNO_REG_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int** hard_regno_nregs ; 

__attribute__((used)) static void
mark_reg (rtx reg, void *xset)
{
  regset set = (regset) xset;
  int regno = REGNO (reg);

  gcc_assert (GET_MODE (reg) != BLKmode);

  SET_REGNO_REG_SET (set, regno);
  if (regno < FIRST_PSEUDO_REGISTER)
    {
      int n = hard_regno_nregs[regno][GET_MODE (reg)];
      while (--n > 0)
	SET_REGNO_REG_SET (set, regno + n);
    }
}