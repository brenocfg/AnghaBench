#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct insn_chain {int /*<<< orphan*/  used_spill_regs; int /*<<< orphan*/  dead_or_set; int /*<<< orphan*/  live_throughout; } ;
typedef  scalar_t__ rtx ;
struct TYPE_2__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  when_needed; int /*<<< orphan*/  opnum; scalar_t__ reg_rtx; } ;
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_HARD_REG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPL_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOR_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_RELOADS ; 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_SET_TO_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_use_by_pseudos (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_reload_reg_in_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int n_reloads ; 
 int /*<<< orphan*/  reg_used_in_insn ; 
 int /*<<< orphan*/  reload_inheritance_insn ; 
 int /*<<< orphan*/  reload_inherited ; 
 int reload_n_operands ; 
 int /*<<< orphan*/  reload_override_in ; 
 int /*<<< orphan*/  reload_reg_unavailable ; 
 int /*<<< orphan*/  reload_reg_used ; 
 int /*<<< orphan*/  reload_reg_used_at_all ; 
 int /*<<< orphan*/  reload_reg_used_for_inherit ; 
 int /*<<< orphan*/ * reload_reg_used_in_inpaddr_addr ; 
 int /*<<< orphan*/ * reload_reg_used_in_input ; 
 int /*<<< orphan*/ * reload_reg_used_in_input_addr ; 
 int /*<<< orphan*/  reload_reg_used_in_insn ; 
 int /*<<< orphan*/  reload_reg_used_in_op_addr ; 
 int /*<<< orphan*/  reload_reg_used_in_op_addr_reload ; 
 int /*<<< orphan*/  reload_reg_used_in_other_addr ; 
 int /*<<< orphan*/ * reload_reg_used_in_outaddr_addr ; 
 int /*<<< orphan*/ * reload_reg_used_in_output ; 
 int /*<<< orphan*/ * reload_reg_used_in_output_addr ; 
 TYPE_1__* rld ; 

__attribute__((used)) static void
choose_reload_regs_init (struct insn_chain *chain, rtx *save_reload_reg_rtx)
{
  int i;

  for (i = 0; i < n_reloads; i++)
    rld[i].reg_rtx = save_reload_reg_rtx[i];

  memset (reload_inherited, 0, MAX_RELOADS);
  memset (reload_inheritance_insn, 0, MAX_RELOADS * sizeof (rtx));
  memset (reload_override_in, 0, MAX_RELOADS * sizeof (rtx));

  CLEAR_HARD_REG_SET (reload_reg_used);
  CLEAR_HARD_REG_SET (reload_reg_used_at_all);
  CLEAR_HARD_REG_SET (reload_reg_used_in_op_addr);
  CLEAR_HARD_REG_SET (reload_reg_used_in_op_addr_reload);
  CLEAR_HARD_REG_SET (reload_reg_used_in_insn);
  CLEAR_HARD_REG_SET (reload_reg_used_in_other_addr);

  CLEAR_HARD_REG_SET (reg_used_in_insn);
  {
    HARD_REG_SET tmp;
    REG_SET_TO_HARD_REG_SET (tmp, &chain->live_throughout);
    IOR_HARD_REG_SET (reg_used_in_insn, tmp);
    REG_SET_TO_HARD_REG_SET (tmp, &chain->dead_or_set);
    IOR_HARD_REG_SET (reg_used_in_insn, tmp);
    compute_use_by_pseudos (&reg_used_in_insn, &chain->live_throughout);
    compute_use_by_pseudos (&reg_used_in_insn, &chain->dead_or_set);
  }

  for (i = 0; i < reload_n_operands; i++)
    {
      CLEAR_HARD_REG_SET (reload_reg_used_in_output[i]);
      CLEAR_HARD_REG_SET (reload_reg_used_in_input[i]);
      CLEAR_HARD_REG_SET (reload_reg_used_in_input_addr[i]);
      CLEAR_HARD_REG_SET (reload_reg_used_in_inpaddr_addr[i]);
      CLEAR_HARD_REG_SET (reload_reg_used_in_output_addr[i]);
      CLEAR_HARD_REG_SET (reload_reg_used_in_outaddr_addr[i]);
    }

  COMPL_HARD_REG_SET (reload_reg_unavailable, chain->used_spill_regs);

  CLEAR_HARD_REG_SET (reload_reg_used_for_inherit);

  for (i = 0; i < n_reloads; i++)
    /* If we have already decided to use a certain register,
       don't use it in another way.  */
    if (rld[i].reg_rtx)
      mark_reload_reg_in_use (REGNO (rld[i].reg_rtx), rld[i].opnum,
			      rld[i].when_needed, rld[i].mode);
}