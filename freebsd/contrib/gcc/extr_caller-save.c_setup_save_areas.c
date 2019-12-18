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
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_HARD_REG_SET (int /*<<< orphan*/ ) ; 
 int FIRST_PSEUDO_REGISTER ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (scalar_t__) ; 
 int MOVE_MAX_WORDS ; 
 scalar_t__ REG_N_CALLS_CROSSED (int) ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int UNITS_PER_WORD ; 
 scalar_t__ VOIDmode ; 
 scalar_t__ adjust_address_nv (scalar_t__,scalar_t__,int) ; 
 scalar_t__ assign_stack_local (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* call_used_regs ; 
 int /*<<< orphan*/  get_frame_alias_set () ; 
 unsigned int** hard_regno_nregs ; 
 int max_regno ; 
 unsigned int* reg_renumber ; 
 int /*<<< orphan*/ * regno_reg_rtx ; 
 scalar_t__** regno_save_mem ; 
 scalar_t__** regno_save_mode ; 
 int /*<<< orphan*/  set_mem_alias_set (scalar_t__,int /*<<< orphan*/ ) ; 

void
setup_save_areas (void)
{
  int i, j, k;
  unsigned int r;
  HARD_REG_SET hard_regs_used;

  /* Allocate space in the save area for the largest multi-register
     pseudos first, then work backwards to single register
     pseudos.  */

  /* Find and record all call-used hard-registers in this function.  */
  CLEAR_HARD_REG_SET (hard_regs_used);
  for (i = FIRST_PSEUDO_REGISTER; i < max_regno; i++)
    if (reg_renumber[i] >= 0 && REG_N_CALLS_CROSSED (i) > 0)
      {
	unsigned int regno = reg_renumber[i];
	unsigned int endregno
	  = regno + hard_regno_nregs[regno][GET_MODE (regno_reg_rtx[i])];

	for (r = regno; r < endregno; r++)
	  if (call_used_regs[r])
	    SET_HARD_REG_BIT (hard_regs_used, r);
      }

  /* Now run through all the call-used hard-registers and allocate
     space for them in the caller-save area.  Try to allocate space
     in a manner which allows multi-register saves/restores to be done.  */

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    for (j = MOVE_MAX_WORDS; j > 0; j--)
      {
	int do_save = 1;

	/* If no mode exists for this size, try another.  Also break out
	   if we have already saved this hard register.  */
	if (regno_save_mode[i][j] == VOIDmode || regno_save_mem[i][1] != 0)
	  continue;

	/* See if any register in this group has been saved.  */
	for (k = 0; k < j; k++)
	  if (regno_save_mem[i + k][1])
	    {
	      do_save = 0;
	      break;
	    }
	if (! do_save)
	  continue;

	for (k = 0; k < j; k++)
	  if (! TEST_HARD_REG_BIT (hard_regs_used, i + k))
	    {
	      do_save = 0;
	      break;
	    }
	if (! do_save)
	  continue;

	/* We have found an acceptable mode to store in.  */
	regno_save_mem[i][j]
	  = assign_stack_local (regno_save_mode[i][j],
				GET_MODE_SIZE (regno_save_mode[i][j]), 0);

	/* Setup single word save area just in case...  */
	for (k = 0; k < j; k++)
	  /* This should not depend on WORDS_BIG_ENDIAN.
	     The order of words in regs is the same as in memory.  */
	  regno_save_mem[i + k][1]
	    = adjust_address_nv (regno_save_mem[i][j],
				 regno_save_mode[i + k][1],
				 k * UNITS_PER_WORD);
      }

  /* Now loop again and set the alias set of any save areas we made to
     the alias set used to represent frame objects.  */
  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    for (j = MOVE_MAX_WORDS; j > 0; j--)
      if (regno_save_mem[i][j] != 0)
	set_mem_alias_set (regno_save_mem[i][j], get_frame_alias_set ());
}