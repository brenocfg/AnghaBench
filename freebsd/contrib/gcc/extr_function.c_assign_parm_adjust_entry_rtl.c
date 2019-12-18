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
struct assign_parm_data_one {int partial; scalar_t__ nominal_mode; scalar_t__ passed_mode; int /*<<< orphan*/ * entry_parm; int /*<<< orphan*/  passed_type; int /*<<< orphan*/ * stack_parm; } ;
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 scalar_t__ BLKmode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 scalar_t__ INTVAL (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ *) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int UNITS_PER_WORD ; 
 scalar_t__ XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t XVECLEN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_group_store (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  int_size_in_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_block_from_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  validize_mem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
assign_parm_adjust_entry_rtl (struct assign_parm_data_one *data)
{
  rtx entry_parm = data->entry_parm;
  rtx stack_parm = data->stack_parm;

  /* If this parm was passed part in regs and part in memory, pretend it
     arrived entirely in memory by pushing the register-part onto the stack.
     In the special case of a DImode or DFmode that is split, we could put
     it together in a pseudoreg directly, but for now that's not worth
     bothering with.  */
  if (data->partial != 0)
    {
      /* Handle calls that pass values in multiple non-contiguous
	 locations.  The Irix 6 ABI has examples of this.  */
      if (GET_CODE (entry_parm) == PARALLEL)
	emit_group_store (validize_mem (stack_parm), entry_parm,
			  data->passed_type, 
			  int_size_in_bytes (data->passed_type));
      else
	{
	  gcc_assert (data->partial % UNITS_PER_WORD == 0);
	  move_block_from_reg (REGNO (entry_parm), validize_mem (stack_parm),
			       data->partial / UNITS_PER_WORD);
	}

      entry_parm = stack_parm;
    }

  /* If we didn't decide this parm came in a register, by default it came
     on the stack.  */
  else if (entry_parm == NULL)
    entry_parm = stack_parm;

  /* When an argument is passed in multiple locations, we can't make use
     of this information, but we can save some copying if the whole argument
     is passed in a single register.  */
  else if (GET_CODE (entry_parm) == PARALLEL
	   && data->nominal_mode != BLKmode
	   && data->passed_mode != BLKmode)
    {
      size_t i, len = XVECLEN (entry_parm, 0);

      for (i = 0; i < len; i++)
	if (XEXP (XVECEXP (entry_parm, 0, i), 0) != NULL_RTX
	    && REG_P (XEXP (XVECEXP (entry_parm, 0, i), 0))
	    && (GET_MODE (XEXP (XVECEXP (entry_parm, 0, i), 0))
		== data->passed_mode)
	    && INTVAL (XEXP (XVECEXP (entry_parm, 0, i), 1)) == 0)
	  {
	    entry_parm = XEXP (XVECEXP (entry_parm, 0, i), 0);
	    break;
	  }
    }

  data->entry_parm = entry_parm;
}