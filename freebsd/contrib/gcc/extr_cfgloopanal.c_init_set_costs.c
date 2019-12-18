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
 int FIRST_PSEUDO_REGISTER ; 
 size_t GENERAL_REGS ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/ * fixed_regs ; 
 int /*<<< orphan*/  gen_raw_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/ * reg_class_contents ; 
 void* seq_cost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 
 int /*<<< orphan*/  target_avail_regs ; 
 int target_pres_cost ; 
 int target_res_regs ; 
 int target_small_cost ; 
 void* target_spill_cost ; 
 int /*<<< orphan*/  validize_mem (int /*<<< orphan*/ ) ; 

void
init_set_costs (void)
{
  rtx seq;
  rtx reg1 = gen_raw_REG (SImode, FIRST_PSEUDO_REGISTER);
  rtx reg2 = gen_raw_REG (SImode, FIRST_PSEUDO_REGISTER + 1);
  rtx addr = gen_raw_REG (Pmode, FIRST_PSEUDO_REGISTER + 2);
  rtx mem = validize_mem (gen_rtx_MEM (SImode, addr));
  unsigned i;

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    if (TEST_HARD_REG_BIT (reg_class_contents[GENERAL_REGS], i)
	&& !fixed_regs[i])
      target_avail_regs++;

  target_res_regs = 3;

  /* These are really just heuristic values.  */

  start_sequence ();
  emit_move_insn (reg1, reg2);
  seq = get_insns ();
  end_sequence ();
  target_small_cost = seq_cost (seq);
  target_pres_cost = 2 * target_small_cost;

  start_sequence ();
  emit_move_insn (mem, reg1);
  emit_move_insn (reg2, mem);
  seq = get_insns ();
  end_sequence ();
  target_spill_cost = seq_cost (seq);
}