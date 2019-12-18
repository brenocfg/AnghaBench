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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int size; int first_reg; size_t mode; int /*<<< orphan*/  freq; int /*<<< orphan*/  n_refs; int /*<<< orphan*/  n_throwing_calls_crossed; int /*<<< orphan*/  n_calls_crossed; int /*<<< orphan*/  min_class; } ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (size_t) ; 
 int /*<<< orphan*/  MODES_TIEABLE_P (size_t,size_t) ; 
 int REGMODE_NATURAL_SIZE (size_t) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_DEAD ; 
 scalar_t__ REG_FREQ (int) ; 
 int /*<<< orphan*/  REG_NO_CONFLICT ; 
 scalar_t__ REG_N_CALLS_CROSSED (int) ; 
 scalar_t__ REG_N_REFS (int) ; 
 scalar_t__ REG_N_THROWING_CALLS_CROSSED (int) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SUBREG ; 
 int SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ UNITS_PER_WORD ; 
 scalar_t__ current_function_has_nonlocal_label ; 
 scalar_t__ find_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_regno_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int** hard_regno_nregs ; 
 TYPE_1__* qty ; 
 int /*<<< orphan*/ * qty_phys_copy_sugg ; 
 int /*<<< orphan*/ * qty_phys_num_copy_sugg ; 
 int /*<<< orphan*/ * qty_phys_num_sugg ; 
 int /*<<< orphan*/ * qty_phys_sugg ; 
 int /*<<< orphan*/  reg_is_born (int /*<<< orphan*/ ,int) ; 
 scalar_t__ reg_meets_class_p (int,int /*<<< orphan*/ ) ; 
 int* reg_next_in_qty ; 
 scalar_t__* reg_offset ; 
 size_t* reg_qty ; 
 scalar_t__ subreg_regno_offset (int,size_t,int,size_t) ; 
 int /*<<< orphan*/  update_qty_class (int,int) ; 

__attribute__((used)) static int
combine_regs (rtx usedreg, rtx setreg, int may_save_copy, int insn_number,
	      rtx insn, int already_dead)
{
  int ureg, sreg;
  int offset = 0;
  int usize, ssize;
  int sqty;

  /* Determine the numbers and sizes of registers being used.  If a subreg
     is present that does not change the entire register, don't consider
     this a copy insn.  */

  while (GET_CODE (usedreg) == SUBREG)
    {
      rtx subreg = SUBREG_REG (usedreg);

      if (REG_P (subreg))
	{
	  if (GET_MODE_SIZE (GET_MODE (subreg)) > UNITS_PER_WORD)
	    may_save_copy = 0;

	  if (REGNO (subreg) < FIRST_PSEUDO_REGISTER)
	    offset += subreg_regno_offset (REGNO (subreg),
					   GET_MODE (subreg),
					   SUBREG_BYTE (usedreg),
					   GET_MODE (usedreg));
	  else
	    offset += (SUBREG_BYTE (usedreg)
		      / REGMODE_NATURAL_SIZE (GET_MODE (usedreg)));
	}

      usedreg = subreg;
    }

  if (!REG_P (usedreg))
    return 0;

  ureg = REGNO (usedreg);
  if (ureg < FIRST_PSEUDO_REGISTER)
    usize = hard_regno_nregs[ureg][GET_MODE (usedreg)];
  else
    usize = ((GET_MODE_SIZE (GET_MODE (usedreg))
	      + (REGMODE_NATURAL_SIZE (GET_MODE (usedreg)) - 1))
	     / REGMODE_NATURAL_SIZE (GET_MODE (usedreg)));

  while (GET_CODE (setreg) == SUBREG)
    {
      rtx subreg = SUBREG_REG (setreg);

      if (REG_P (subreg))
	{
	  if (GET_MODE_SIZE (GET_MODE (subreg)) > UNITS_PER_WORD)
	    may_save_copy = 0;

	  if (REGNO (subreg) < FIRST_PSEUDO_REGISTER)
	    offset -= subreg_regno_offset (REGNO (subreg),
					   GET_MODE (subreg),
					   SUBREG_BYTE (setreg),
					   GET_MODE (setreg));
	  else
	    offset -= (SUBREG_BYTE (setreg)
		      / REGMODE_NATURAL_SIZE (GET_MODE (setreg)));
	}

      setreg = subreg;
    }

  if (!REG_P (setreg))
    return 0;

  sreg = REGNO (setreg);
  if (sreg < FIRST_PSEUDO_REGISTER)
    ssize = hard_regno_nregs[sreg][GET_MODE (setreg)];
  else
    ssize = ((GET_MODE_SIZE (GET_MODE (setreg))
	      + (REGMODE_NATURAL_SIZE (GET_MODE (setreg)) - 1))
	     / REGMODE_NATURAL_SIZE (GET_MODE (setreg)));

  /* If UREG is a pseudo-register that hasn't already been assigned a
     quantity number, it means that it is not local to this block or dies
     more than once.  In either event, we can't do anything with it.  */
  if ((ureg >= FIRST_PSEUDO_REGISTER && reg_qty[ureg] < 0)
      /* Do not combine registers unless one fits within the other.  */
      || (offset > 0 && usize + offset > ssize)
      || (offset < 0 && usize + offset < ssize)
      /* Do not combine with a smaller already-assigned object
	 if that smaller object is already combined with something bigger.  */
      || (ssize > usize && ureg >= FIRST_PSEUDO_REGISTER
	  && usize < qty[reg_qty[ureg]].size)
      /* Can't combine if SREG is not a register we can allocate.  */
      || (sreg >= FIRST_PSEUDO_REGISTER && reg_qty[sreg] == -1)
      /* Don't combine with a pseudo mentioned in a REG_NO_CONFLICT note.
	 These have already been taken care of.  This probably wouldn't
	 combine anyway, but don't take any chances.  */
      || (ureg >= FIRST_PSEUDO_REGISTER
	  && find_reg_note (insn, REG_NO_CONFLICT, usedreg))
      /* Don't tie something to itself.  In most cases it would make no
	 difference, but it would screw up if the reg being tied to itself
	 also dies in this insn.  */
      || ureg == sreg
      /* Don't try to connect two different hardware registers.  */
      || (ureg < FIRST_PSEUDO_REGISTER && sreg < FIRST_PSEUDO_REGISTER)
      /* Don't connect two different machine modes if they have different
	 implications as to which registers may be used.  */
      || !MODES_TIEABLE_P (GET_MODE (usedreg), GET_MODE (setreg)))
    return 0;

  /* Now, if UREG is a hard reg and SREG is a pseudo, record the hard reg in
     qty_phys_sugg for the pseudo instead of tying them.

     Return "failure" so that the lifespan of UREG is terminated here;
     that way the two lifespans will be disjoint and nothing will prevent
     the pseudo reg from being given this hard reg.  */

  if (ureg < FIRST_PSEUDO_REGISTER)
    {
      /* Allocate a quantity number so we have a place to put our
	 suggestions.  */
      if (reg_qty[sreg] == -2)
	reg_is_born (setreg, 2 * insn_number);

      if (reg_qty[sreg] >= 0)
	{
	  if (may_save_copy
	      && ! TEST_HARD_REG_BIT (qty_phys_copy_sugg[reg_qty[sreg]], ureg))
	    {
	      SET_HARD_REG_BIT (qty_phys_copy_sugg[reg_qty[sreg]], ureg);
	      qty_phys_num_copy_sugg[reg_qty[sreg]]++;
	    }
	  else if (! TEST_HARD_REG_BIT (qty_phys_sugg[reg_qty[sreg]], ureg))
	    {
	      SET_HARD_REG_BIT (qty_phys_sugg[reg_qty[sreg]], ureg);
	      qty_phys_num_sugg[reg_qty[sreg]]++;
	    }
	}
      return 0;
    }

  /* Similarly for SREG a hard register and UREG a pseudo register.  */

  if (sreg < FIRST_PSEUDO_REGISTER)
    {
      if (may_save_copy
	  && ! TEST_HARD_REG_BIT (qty_phys_copy_sugg[reg_qty[ureg]], sreg))
	{
	  SET_HARD_REG_BIT (qty_phys_copy_sugg[reg_qty[ureg]], sreg);
	  qty_phys_num_copy_sugg[reg_qty[ureg]]++;
	}
      else if (! TEST_HARD_REG_BIT (qty_phys_sugg[reg_qty[ureg]], sreg))
	{
	  SET_HARD_REG_BIT (qty_phys_sugg[reg_qty[ureg]], sreg);
	  qty_phys_num_sugg[reg_qty[ureg]]++;
	}
      return 0;
    }

  /* At this point we know that SREG and UREG are both pseudos.
     Do nothing if SREG already has a quantity or is a register that we
     don't allocate.  */
  if (reg_qty[sreg] >= -1
      /* If we are not going to let any regs live across calls,
	 don't tie a call-crossing reg to a non-call-crossing reg.  */
      || (current_function_has_nonlocal_label
	  && ((REG_N_CALLS_CROSSED (ureg) > 0)
	      != (REG_N_CALLS_CROSSED (sreg) > 0))))
    return 0;

  /* We don't already know about SREG, so tie it to UREG
     if this is the last use of UREG, provided the classes they want
     are compatible.  */

  if ((already_dead || find_regno_note (insn, REG_DEAD, ureg))
      && reg_meets_class_p (sreg, qty[reg_qty[ureg]].min_class))
    {
      /* Add SREG to UREG's quantity.  */
      sqty = reg_qty[ureg];
      reg_qty[sreg] = sqty;
      reg_offset[sreg] = reg_offset[ureg] + offset;
      reg_next_in_qty[sreg] = qty[sqty].first_reg;
      qty[sqty].first_reg = sreg;

      /* If SREG's reg class is smaller, set qty[SQTY].min_class.  */
      update_qty_class (sqty, sreg);

      /* Update info about quantity SQTY.  */
      qty[sqty].n_calls_crossed += REG_N_CALLS_CROSSED (sreg);
      qty[sqty].n_throwing_calls_crossed
	+= REG_N_THROWING_CALLS_CROSSED (sreg);
      qty[sqty].n_refs += REG_N_REFS (sreg);
      qty[sqty].freq += REG_FREQ (sreg);
      if (usize < ssize)
	{
	  int i;

	  for (i = qty[sqty].first_reg; i >= 0; i = reg_next_in_qty[i])
	    reg_offset[i] -= offset;

	  qty[sqty].size = ssize;
	  qty[sqty].mode = GET_MODE (setreg);
	}
    }
  else
    return 0;

  return 1;
}