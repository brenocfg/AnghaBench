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

/* Variables and functions */
 int /*<<< orphan*/  BLKmode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ HAVE_store_multiple ; 
 int /*<<< orphan*/  delete_insns_since (scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gen_store_multiple (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_last_insn () ; 
 scalar_t__ operand_subword (scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  word_mode ; 

void
move_block_from_reg (int regno, rtx x, int nregs)
{
  int i;

  if (nregs == 0)
    return;

  /* See if the machine can do this with a store multiple insn.  */
#ifdef HAVE_store_multiple
  if (HAVE_store_multiple)
    {
      rtx last = get_last_insn ();
      rtx pat = gen_store_multiple (x, gen_rtx_REG (word_mode, regno),
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
    {
      rtx tem = operand_subword (x, i, 1, BLKmode);

      gcc_assert (tem);

      emit_move_insn (tem, gen_rtx_REG (word_mode, regno + i));
    }
}