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
 scalar_t__ CC0 ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dead_or_set_regno_p (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 unsigned int** hard_regno_nregs ; 

int
dead_or_set_p (rtx insn, rtx x)
{
  unsigned int regno, last_regno;
  unsigned int i;

  /* Can't use cc0_rtx below since this file is used by genattrtab.c.  */
  if (GET_CODE (x) == CC0)
    return 1;

  gcc_assert (REG_P (x));

  regno = REGNO (x);
  last_regno = (regno >= FIRST_PSEUDO_REGISTER ? regno
		: regno + hard_regno_nregs[regno][GET_MODE (x)] - 1);

  for (i = regno; i <= last_regno; i++)
    if (! dead_or_set_regno_p (insn, i))
      return 0;

  return 1;
}