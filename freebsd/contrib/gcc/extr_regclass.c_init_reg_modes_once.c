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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  HARD_REGNO_NREGS (int,int) ; 
 int MAX_MACHINE_MODE ; 
 scalar_t__ VOIDmode ; 
 scalar_t__ choose_hard_reg_mode (int,int,int) ; 
 int /*<<< orphan*/ ** hard_regno_nregs ; 
 scalar_t__* reg_raw_mode ; 
 scalar_t__ word_mode ; 

void
init_reg_modes_once (void)
{
  int i, j;

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    for (j = 0; j < MAX_MACHINE_MODE; j++)
      hard_regno_nregs[i][j] = HARD_REGNO_NREGS(i, (enum machine_mode)j);

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    {
      reg_raw_mode[i] = choose_hard_reg_mode (i, 1, false);

      /* If we couldn't find a valid mode, just use the previous mode.
         ??? One situation in which we need to do this is on the mips where
	 HARD_REGNO_NREGS (fpreg, [SD]Fmode) returns 2.  Ideally we'd like
	 to use DF mode for the even registers and VOIDmode for the odd
	 (for the cpu models where the odd ones are inaccessible).  */
      if (reg_raw_mode[i] == VOIDmode)
	reg_raw_mode[i] = i == 0 ? word_mode : reg_raw_mode[i-1];
    }
}