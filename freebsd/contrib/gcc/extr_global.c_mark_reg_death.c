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
 int /*<<< orphan*/  CLEAR_ALLOCNO_LIVE (scalar_t__) ; 
 int /*<<< orphan*/  CLEAR_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int FIRST_PSEUDO_REGISTER ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fixed_regs ; 
 int** hard_regno_nregs ; 
 int /*<<< orphan*/  hard_regs_live ; 
 scalar_t__* reg_allocno ; 
 int* reg_renumber ; 

__attribute__((used)) static void
mark_reg_death (rtx reg)
{
  int regno = REGNO (reg);

  /* Either this is one of the max_allocno pseudo regs not allocated,
     or it is a hardware reg.  First handle the pseudo-regs.  */
  if (regno >= FIRST_PSEUDO_REGISTER)
    {
      if (reg_allocno[regno] >= 0)
	CLEAR_ALLOCNO_LIVE (reg_allocno[regno]);
    }

  /* For pseudo reg, see if it has been assigned a hardware reg.  */
  if (reg_renumber[regno] >= 0)
    regno = reg_renumber[regno];

  /* Handle hardware regs (and pseudos allocated to hard regs).  */
  if (regno < FIRST_PSEUDO_REGISTER && ! fixed_regs[regno])
    {
      /* Pseudo regs already assigned hardware regs are treated
	 almost the same as explicit hardware regs.  */
      int last = regno + hard_regno_nregs[regno][GET_MODE (reg)];
      while (regno < last)
	{
	  CLEAR_HARD_REG_BIT (hard_regs_live, regno);
	  regno++;
	}
    }
}