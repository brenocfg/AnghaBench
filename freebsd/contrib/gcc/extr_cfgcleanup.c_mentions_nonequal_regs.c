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
 int FIRST_PSEUDO_REGISTER ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO_REG_SET_P (int /*<<< orphan*/ ,int) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int** hard_regno_nregs ; 

__attribute__((used)) static int
mentions_nonequal_regs (rtx *x, void *data)
{
  regset nonequal = (regset) data;
  if (REG_P (*x))
    {
      int regno;

      regno = REGNO (*x);
      if (REGNO_REG_SET_P (nonequal, regno))
	return 1;
      if (regno < FIRST_PSEUDO_REGISTER)
	{
	  int n = hard_regno_nregs[regno][GET_MODE (*x)];
	  while (--n > 0)
	    if (REGNO_REG_SET_P (nonequal, regno + n))
	      return 1;
	}
    }
  return 0;
}