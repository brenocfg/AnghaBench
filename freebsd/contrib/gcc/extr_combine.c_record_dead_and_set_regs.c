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
typedef  scalar_t__ rtx ;
struct TYPE_2__ {scalar_t__ truncated_to_mode; scalar_t__ last_death; scalar_t__ last_set_sign_bit_copies; scalar_t__ last_set_nonzero_bits; scalar_t__ last_set_mode; scalar_t__ last_set_value; } ;

/* Variables and functions */
 scalar_t__ CALL_P (scalar_t__) ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 size_t GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  INSN_CUID (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 unsigned int REGNO (scalar_t__) ; 
 scalar_t__ REG_DEAD ; 
 scalar_t__ REG_INC ; 
 scalar_t__ REG_NOTES (scalar_t__) ; 
 scalar_t__ REG_NOTE_KIND (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int** hard_regno_nregs ; 
 int /*<<< orphan*/  last_call_cuid ; 
 int /*<<< orphan*/  mem_last_set ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  record_dead_and_set_regs_1 ; 
 int /*<<< orphan*/  record_value_for_reg (scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_1__* reg_stat ; 
 int /*<<< orphan*/  regs_invalidated_by_call ; 

__attribute__((used)) static void
record_dead_and_set_regs (rtx insn)
{
  rtx link;
  unsigned int i;

  for (link = REG_NOTES (insn); link; link = XEXP (link, 1))
    {
      if (REG_NOTE_KIND (link) == REG_DEAD
	  && REG_P (XEXP (link, 0)))
	{
	  unsigned int regno = REGNO (XEXP (link, 0));
	  unsigned int endregno
	    = regno + (regno < FIRST_PSEUDO_REGISTER
		       ? hard_regno_nregs[regno][GET_MODE (XEXP (link, 0))]
		       : 1);

	  for (i = regno; i < endregno; i++)
	    reg_stat[i].last_death = insn;
	}
      else if (REG_NOTE_KIND (link) == REG_INC)
	record_value_for_reg (XEXP (link, 0), insn, NULL_RTX);
    }

  if (CALL_P (insn))
    {
      for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
	if (TEST_HARD_REG_BIT (regs_invalidated_by_call, i))
	  {
	    reg_stat[i].last_set_value = 0;
	    reg_stat[i].last_set_mode = 0;
	    reg_stat[i].last_set_nonzero_bits = 0;
	    reg_stat[i].last_set_sign_bit_copies = 0;
	    reg_stat[i].last_death = 0;
	    reg_stat[i].truncated_to_mode = 0;
	  }

      last_call_cuid = mem_last_set = INSN_CUID (insn);

      /* We can't combine into a call pattern.  Remember, though, that
	 the return value register is set at this CUID.  We could
	 still replace a register with the return value from the
	 wrong subroutine call!  */
      note_stores (PATTERN (insn), record_dead_and_set_regs_1, NULL_RTX);
    }
  else
    note_stores (PATTERN (insn), record_dead_and_set_regs_1, insn);
}