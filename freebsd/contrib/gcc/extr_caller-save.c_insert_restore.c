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
struct insn_chain {int /*<<< orphan*/  dead_or_set; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 size_t GET_MODE (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  SET_REGNO_REG_SET (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int VOIDmode ; 
 scalar_t__ adjust_address (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_rtx (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_REG (size_t,int) ; 
 scalar_t__ gen_rtx_SET (int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__** hard_regno_nregs ; 
 int /*<<< orphan*/  hard_regs_saved ; 
 struct insn_chain* insert_one_insn (struct insn_chain*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  n_regs_saved ; 
 int** reg_restore_code ; 
 scalar_t__** regno_save_mem ; 

__attribute__((used)) static int
insert_restore (struct insn_chain *chain, int before_p, int regno,
		int maxrestore, enum machine_mode *save_mode)
{
  int i, k;
  rtx pat = NULL_RTX;
  int code;
  unsigned int numregs = 0;
  struct insn_chain *new;
  rtx mem;

  /* A common failure mode if register status is not correct in the
     RTL is for this routine to be called with a REGNO we didn't
     expect to save.  That will cause us to write an insn with a (nil)
     SET_DEST or SET_SRC.  Instead of doing so and causing a crash
     later, check for this common case here instead.  This will remove
     one step in debugging such problems.  */
  gcc_assert (regno_save_mem[regno][1]);

  /* Get the pattern to emit and update our status.

     See if we can restore `maxrestore' registers at once.  Work
     backwards to the single register case.  */
  for (i = maxrestore; i > 0; i--)
    {
      int j;
      int ok = 1;

      if (regno_save_mem[regno][i] == 0)
	continue;

      for (j = 0; j < i; j++)
	if (! TEST_HARD_REG_BIT (hard_regs_saved, regno + j))
	  {
	    ok = 0;
	    break;
	  }
      /* Must do this one restore at a time.  */
      if (! ok)
	continue;

      numregs = i;
      break;
    }

  mem = regno_save_mem [regno][numregs];
  if (save_mode [regno] != VOIDmode
      && save_mode [regno] != GET_MODE (mem)
      && numregs == (unsigned int) hard_regno_nregs[regno][save_mode [regno]])
    mem = adjust_address (mem, save_mode[regno], 0);
  else
    mem = copy_rtx (mem);
  pat = gen_rtx_SET (VOIDmode,
		     gen_rtx_REG (GET_MODE (mem),
				  regno), mem);
  code = reg_restore_code[regno][GET_MODE (mem)];
  new = insert_one_insn (chain, before_p, code, pat);

  /* Clear status for all registers we restored.  */
  for (k = 0; k < i; k++)
    {
      CLEAR_HARD_REG_BIT (hard_regs_saved, regno + k);
      SET_REGNO_REG_SET (&new->dead_or_set, regno + k);
      n_regs_saved--;
    }

  /* Tell our callers how many extra registers we saved/restored.  */
  return numregs - 1;
}