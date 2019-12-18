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
 int /*<<< orphan*/  FUNCTION_ARG_REGNO_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GR_REGNO_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  TARGET_CONST_GP ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_call_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_call_nogp (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_call_value_nogp (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_MEM (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_POST_DEC (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_POST_INC (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_sibcall_nogp (scalar_t__) ; 
 int /*<<< orphan*/  ia64_reload_gp () ; 
 scalar_t__ pic_offset_table_rtx ; 
 int /*<<< orphan*/  regs_invalidated_by_call ; 

void
ia64_split_call (rtx retval, rtx addr, rtx retaddr, rtx scratch_r,
		 rtx scratch_b, int noreturn_p, int sibcall_p)
{
  rtx insn;
  bool is_desc = false;

  /* If we find we're calling through a register, then we're actually
     calling through a descriptor, so load up the values.  */
  if (REG_P (addr) && GR_REGNO_P (REGNO (addr)))
    {
      rtx tmp;
      bool addr_dead_p;

      /* ??? We are currently constrained to *not* use peep2, because
	 we can legitimately change the global lifetime of the GP
	 (in the form of killing where previously live).  This is
	 because a call through a descriptor doesn't use the previous
	 value of the GP, while a direct call does, and we do not
	 commit to either form until the split here.

	 That said, this means that we lack precise life info for
	 whether ADDR is dead after this call.  This is not terribly
	 important, since we can fix things up essentially for free
	 with the POST_DEC below, but it's nice to not use it when we
	 can immediately tell it's not necessary.  */
      addr_dead_p = ((noreturn_p || sibcall_p
		      || TEST_HARD_REG_BIT (regs_invalidated_by_call,
					    REGNO (addr)))
		     && !FUNCTION_ARG_REGNO_P (REGNO (addr)));

      /* Load the code address into scratch_b.  */
      tmp = gen_rtx_POST_INC (Pmode, addr);
      tmp = gen_rtx_MEM (Pmode, tmp);
      emit_move_insn (scratch_r, tmp);
      emit_move_insn (scratch_b, scratch_r);

      /* Load the GP address.  If ADDR is not dead here, then we must
	 revert the change made above via the POST_INCREMENT.  */
      if (!addr_dead_p)
	tmp = gen_rtx_POST_DEC (Pmode, addr);
      else
	tmp = addr;
      tmp = gen_rtx_MEM (Pmode, tmp);
      emit_move_insn (pic_offset_table_rtx, tmp);

      is_desc = true;
      addr = scratch_b;
    }

  if (sibcall_p)
    insn = gen_sibcall_nogp (addr);
  else if (retval)
    insn = gen_call_value_nogp (retval, addr, retaddr);
  else
    insn = gen_call_nogp (addr, retaddr);
  emit_call_insn (insn);

  if ((!TARGET_CONST_GP || is_desc) && !noreturn_p && !sibcall_p)
    ia64_reload_gp ();
}