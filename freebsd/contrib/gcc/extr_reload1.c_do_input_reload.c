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
struct reload {scalar_t__ in; scalar_t__ in_reg; scalar_t__ out_reg; scalar_t__ reg_rtx; scalar_t__ when_needed; scalar_t__ out; } ;
struct insn_chain {scalar_t__ insn; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 size_t FIRST_PSEUDO_REGISTER ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 size_t REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ RELOAD_FOR_INPUT ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ dead_or_set_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  delete_output_reload (scalar_t__,int,size_t) ; 
 int /*<<< orphan*/  emit_input_reload_insns (struct insn_chain*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ optimize ; 
 size_t* reg_reloaded_contents ; 
 int /*<<< orphan*/  reg_reloaded_valid ; 
 scalar_t__* regno_reg_rtx ; 
 scalar_t__* reload_inherited ; 
 scalar_t__* reload_override_in ; 
 size_t* reload_spill_index ; 
 scalar_t__ rld ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__* spill_reg_store ; 
 scalar_t__* spill_reg_stored_to ; 

__attribute__((used)) static void
do_input_reload (struct insn_chain *chain, struct reload *rl, int j)
{
  rtx insn = chain->insn;
  rtx old = (rl->in && MEM_P (rl->in)
	     ? rl->in_reg : rl->in);

  if (old != 0
      /* AUTO_INC reloads need to be handled even if inherited.  We got an
	 AUTO_INC reload if reload_out is set but reload_out_reg isn't.  */
      && (! reload_inherited[j] || (rl->out && ! rl->out_reg))
      && ! rtx_equal_p (rl->reg_rtx, old)
      && rl->reg_rtx != 0)
    emit_input_reload_insns (chain, rld + j, old, j);

  /* When inheriting a wider reload, we have a MEM in rl->in,
     e.g. inheriting a SImode output reload for
     (mem:HI (plus:SI (reg:SI 14 fp) (const_int 10)))  */
  if (optimize && reload_inherited[j] && rl->in
      && MEM_P (rl->in)
      && MEM_P (rl->in_reg)
      && reload_spill_index[j] >= 0
      && TEST_HARD_REG_BIT (reg_reloaded_valid, reload_spill_index[j]))
    rl->in = regno_reg_rtx[reg_reloaded_contents[reload_spill_index[j]]];

  /* If we are reloading a register that was recently stored in with an
     output-reload, see if we can prove there was
     actually no need to store the old value in it.  */

  if (optimize
      /* Only attempt this for input reloads; for RELOAD_OTHER we miss
	 that there may be multiple uses of the previous output reload.
	 Restricting to RELOAD_FOR_INPUT is mostly paranoia.  */
      && rl->when_needed == RELOAD_FOR_INPUT
      && (reload_inherited[j] || reload_override_in[j])
      && rl->reg_rtx
      && REG_P (rl->reg_rtx)
      && spill_reg_store[REGNO (rl->reg_rtx)] != 0
#if 0
      /* There doesn't seem to be any reason to restrict this to pseudos
	 and doing so loses in the case where we are copying from a
	 register of the wrong class.  */
      && (REGNO (spill_reg_stored_to[REGNO (rl->reg_rtx)])
	  >= FIRST_PSEUDO_REGISTER)
#endif
      /* The insn might have already some references to stackslots
	 replaced by MEMs, while reload_out_reg still names the
	 original pseudo.  */
      && (dead_or_set_p (insn,
			 spill_reg_stored_to[REGNO (rl->reg_rtx)])
	  || rtx_equal_p (spill_reg_stored_to[REGNO (rl->reg_rtx)],
			  rl->out_reg)))
    delete_output_reload (insn, j, REGNO (rl->reg_rtx));
}