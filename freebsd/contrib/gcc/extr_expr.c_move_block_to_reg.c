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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ HAVE_load_multiple ; 
 int /*<<< orphan*/  LEGITIMATE_CONSTANT_P (scalar_t__) ; 
 int /*<<< orphan*/  delete_insns_since (scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_const_mem (int,scalar_t__) ; 
 scalar_t__ gen_load_multiple (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_last_insn () ; 
 int /*<<< orphan*/  operand_subword_force (scalar_t__,int,int) ; 
 scalar_t__ validize_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  word_mode ; 

void
move_block_to_reg (int regno, rtx x, int nregs, enum machine_mode mode)
{
  int i;
#ifdef HAVE_load_multiple
  rtx pat;
  rtx last;
#endif

  if (nregs == 0)
    return;

  if (CONSTANT_P (x) && ! LEGITIMATE_CONSTANT_P (x))
    x = validize_mem (force_const_mem (mode, x));

  /* See if the machine can do this with a load multiple insn.  */
#ifdef HAVE_load_multiple
  if (HAVE_load_multiple)
    {
      last = get_last_insn ();
      pat = gen_load_multiple (gen_rtx_REG (word_mode, regno), x,
			       GEN_INT (nregs));
      if (pat)
	{
	  emit_insn (pat);
	  return;
	}
      else
	delete_insns_since (last);
    }
#endif

  for (i = 0; i < nregs; i++)
    emit_move_insn (gen_rtx_REG (word_mode, regno + i),
		    operand_subword_force (x, i, mode));
}