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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 unsigned int FIRST_PSEUDO_REGISTER ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ HARD_REGNO_MODE_OK (unsigned int,int) ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int REG_N_SETS (unsigned int) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_USERVAR_P (int /*<<< orphan*/ ) ; 
 scalar_t__** hard_regno_nregs ; 

__attribute__((used)) static bool
can_change_dest_mode (rtx x, int added_sets, enum machine_mode mode)
{
  unsigned int regno;

  if (!REG_P(x))
    return false;

  regno = REGNO (x);
  /* Allow hard registers if the new mode is legal, and occupies no more
     registers than the old mode.  */
  if (regno < FIRST_PSEUDO_REGISTER)
    return (HARD_REGNO_MODE_OK (regno, mode)
	    && (hard_regno_nregs[regno][GET_MODE (x)]
		>= hard_regno_nregs[regno][mode]));

  /* Or a pseudo that is only used once.  */
  return (REG_N_SETS (regno) == 1 && !added_sets
	  && !REG_USERVAR_P (x));
}