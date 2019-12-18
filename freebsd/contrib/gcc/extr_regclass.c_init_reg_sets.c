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

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_HARD_REG_SET (int /*<<< orphan*/ ) ; 
 int FIRST_PSEUDO_REGISTER ; 
 int N_REG_CLASSES ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  call_used_regs ; 
 int /*<<< orphan*/  fixed_regs ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  global_regs ; 
 int /*<<< orphan*/  initial_call_used_regs ; 
 int /*<<< orphan*/  initial_fixed_regs ; 
 unsigned int** int_reg_class_contents ; 
 int* inv_reg_alloc_order ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t* reg_alloc_order ; 
 int /*<<< orphan*/ * reg_class_contents ; 

void
init_reg_sets (void)
{
  int i, j;

  /* First copy the register information from the initial int form into
     the regsets.  */

  for (i = 0; i < N_REG_CLASSES; i++)
    {
      CLEAR_HARD_REG_SET (reg_class_contents[i]);

      /* Note that we hard-code 32 here, not HOST_BITS_PER_INT.  */
      for (j = 0; j < FIRST_PSEUDO_REGISTER; j++)
	if (int_reg_class_contents[i][j / 32]
	    & ((unsigned) 1 << (j % 32)))
	  SET_HARD_REG_BIT (reg_class_contents[i], j);
    }

  /* Sanity check: make sure the target macros FIXED_REGISTERS and
     CALL_USED_REGISTERS had the right number of initializers.  */
  gcc_assert (sizeof fixed_regs == sizeof initial_fixed_regs);
  gcc_assert (sizeof call_used_regs == sizeof initial_call_used_regs);

  memcpy (fixed_regs, initial_fixed_regs, sizeof fixed_regs);
  memcpy (call_used_regs, initial_call_used_regs, sizeof call_used_regs);
  memset (global_regs, 0, sizeof global_regs);

#ifdef REG_ALLOC_ORDER
  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    inv_reg_alloc_order[reg_alloc_order[i]] = i;
#endif
}