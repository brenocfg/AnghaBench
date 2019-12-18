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
 scalar_t__ CALL_P (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  LINK_REGISTER_REGNUM ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  REG_INC ; 
 int /*<<< orphan*/  SIBLING_CALL_P (scalar_t__) ; 
 scalar_t__ current_function_is_thunk ; 
 scalar_t__ find_regno_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  pop_topmost_sequence () ; 
 int /*<<< orphan*/  prologue_epilogue_contains (scalar_t__) ; 
 int /*<<< orphan*/  push_topmost_sequence () ; 
 scalar_t__ set_of (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
rs6000_ra_ever_killed (void)
{
  rtx top;
  rtx reg;
  rtx insn;

  if (current_function_is_thunk)
    return 0;

  /* regs_ever_live has LR marked as used if any sibcalls are present,
     but this should not force saving and restoring in the
     pro/epilogue.  Likewise, reg_set_between_p thinks a sibcall
     clobbers LR, so that is inappropriate.  */

  /* Also, the prologue can generate a store into LR that
     doesn't really count, like this:

        move LR->R0
        bcl to set PIC register
        move LR->R31
        move R0->LR

     When we're called from the epilogue, we need to avoid counting
     this as a store.  */

  push_topmost_sequence ();
  top = get_insns ();
  pop_topmost_sequence ();
  reg = gen_rtx_REG (Pmode, LINK_REGISTER_REGNUM);

  for (insn = NEXT_INSN (top); insn != NULL_RTX; insn = NEXT_INSN (insn))
    {
      if (INSN_P (insn))
	{
	  if (CALL_P (insn))
	    {
	      if (!SIBLING_CALL_P (insn))
		return 1;
	    }
	  else if (find_regno_note (insn, REG_INC, LINK_REGISTER_REGNUM))
	    return 1;
	  else if (set_of (reg, insn) != NULL_RTX
		   && !prologue_epilogue_contains (insn))
	    return 1;
    	}
    }
  return 0;
}