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
struct TYPE_2__ {scalar_t__ in; scalar_t__ when_needed; scalar_t__ out; scalar_t__ reg_rtx; int opnum; } ;

/* Variables and functions */
 int MAX_RECOG_OPERANDS ; 
 scalar_t__ RELOAD_FOR_INPADDR_ADDRESS ; 
 scalar_t__ RELOAD_FOR_INPUT ; 
 scalar_t__ RELOAD_FOR_INPUT_ADDRESS ; 
 scalar_t__ RELOAD_FOR_OPERAND_ADDRESS ; 
 scalar_t__ RELOAD_FOR_OTHER_ADDRESS ; 
 scalar_t__ RELOAD_FOR_OUTPUT ; 
 scalar_t__ RELOAD_FOR_OUTPUT_ADDRESS ; 
 scalar_t__ RELOAD_OTHER ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int n_reloads ; 
 scalar_t__ reg_overlap_mentioned_for_reload_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  reg_overlap_mentioned_p (scalar_t__,scalar_t__) ; 
 scalar_t__ reg_set_p (scalar_t__,int /*<<< orphan*/ ) ; 
 int* reload_spill_index ; 
 TYPE_1__* rld ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  transfer_replacements (int,int) ; 

__attribute__((used)) static void
merge_assigned_reloads (rtx insn)
{
  int i, j;

  /* Scan all the reloads looking for ones that only load values and
     are not already RELOAD_OTHER and ones whose reload_reg_rtx are
     assigned and not modified by INSN.  */

  for (i = 0; i < n_reloads; i++)
    {
      int conflicting_input = 0;
      int max_input_address_opnum = -1;
      int min_conflicting_input_opnum = MAX_RECOG_OPERANDS;

      if (rld[i].in == 0 || rld[i].when_needed == RELOAD_OTHER
	  || rld[i].out != 0 || rld[i].reg_rtx == 0
	  || reg_set_p (rld[i].reg_rtx, insn))
	continue;

      /* Look at all other reloads.  Ensure that the only use of this
	 reload_reg_rtx is in a reload that just loads the same value
	 as we do.  Note that any secondary reloads must be of the identical
	 class since the values, modes, and result registers are the
	 same, so we need not do anything with any secondary reloads.  */

      for (j = 0; j < n_reloads; j++)
	{
	  if (i == j || rld[j].reg_rtx == 0
	      || ! reg_overlap_mentioned_p (rld[j].reg_rtx,
					    rld[i].reg_rtx))
	    continue;

	  if (rld[j].when_needed == RELOAD_FOR_INPUT_ADDRESS
	      && rld[j].opnum > max_input_address_opnum)
	    max_input_address_opnum = rld[j].opnum;

	  /* If the reload regs aren't exactly the same (e.g, different modes)
	     or if the values are different, we can't merge this reload.
	     But if it is an input reload, we might still merge
	     RELOAD_FOR_INPUT_ADDRESS and RELOAD_FOR_OTHER_ADDRESS reloads.  */

	  if (! rtx_equal_p (rld[i].reg_rtx, rld[j].reg_rtx)
	      || rld[j].out != 0 || rld[j].in == 0
	      || ! rtx_equal_p (rld[i].in, rld[j].in))
	    {
	      if (rld[j].when_needed != RELOAD_FOR_INPUT
		  || ((rld[i].when_needed != RELOAD_FOR_INPUT_ADDRESS
		       || rld[i].opnum > rld[j].opnum)
		      && rld[i].when_needed != RELOAD_FOR_OTHER_ADDRESS))
		break;
	      conflicting_input = 1;
	      if (min_conflicting_input_opnum > rld[j].opnum)
		min_conflicting_input_opnum = rld[j].opnum;
	    }
	}

      /* If all is OK, merge the reloads.  Only set this to RELOAD_OTHER if
	 we, in fact, found any matching reloads.  */

      if (j == n_reloads
	  && max_input_address_opnum <= min_conflicting_input_opnum)
	{
	  gcc_assert (rld[i].when_needed != RELOAD_FOR_OUTPUT);

	  for (j = 0; j < n_reloads; j++)
	    if (i != j && rld[j].reg_rtx != 0
		&& rtx_equal_p (rld[i].reg_rtx, rld[j].reg_rtx)
		&& (! conflicting_input
		    || rld[j].when_needed == RELOAD_FOR_INPUT_ADDRESS
		    || rld[j].when_needed == RELOAD_FOR_OTHER_ADDRESS))
	      {
		rld[i].when_needed = RELOAD_OTHER;
		rld[j].in = 0;
		reload_spill_index[j] = -1;
		transfer_replacements (i, j);
	      }

	  /* If this is now RELOAD_OTHER, look for any reloads that
	     load parts of this operand and set them to
	     RELOAD_FOR_OTHER_ADDRESS if they were for inputs,
	     RELOAD_OTHER for outputs.  Note that this test is
	     equivalent to looking for reloads for this operand
	     number.

	     We must take special care with RELOAD_FOR_OUTPUT_ADDRESS;
	     it may share registers with a RELOAD_FOR_INPUT, so we can
	     not change it to RELOAD_FOR_OTHER_ADDRESS.  We should
	     never need to, since we do not modify RELOAD_FOR_OUTPUT.

	     It is possible that the RELOAD_FOR_OPERAND_ADDRESS
	     instruction is assigned the same register as the earlier
	     RELOAD_FOR_OTHER_ADDRESS instruction.  Merging these two
	     instructions will cause the RELOAD_FOR_OTHER_ADDRESS
	     instruction to be deleted later on.  */

	  if (rld[i].when_needed == RELOAD_OTHER)
	    for (j = 0; j < n_reloads; j++)
	      if (rld[j].in != 0
		  && rld[j].when_needed != RELOAD_OTHER
		  && rld[j].when_needed != RELOAD_FOR_OTHER_ADDRESS
		  && rld[j].when_needed != RELOAD_FOR_OUTPUT_ADDRESS
		  && rld[j].when_needed != RELOAD_FOR_OPERAND_ADDRESS
		  && (! conflicting_input
		      || rld[j].when_needed == RELOAD_FOR_INPUT_ADDRESS
		      || rld[j].when_needed == RELOAD_FOR_INPADDR_ADDRESS)
		  && reg_overlap_mentioned_for_reload_p (rld[j].in,
							 rld[i].in))
		{
		  int k;

		  rld[j].when_needed
		    = ((rld[j].when_needed == RELOAD_FOR_INPUT_ADDRESS
			|| rld[j].when_needed == RELOAD_FOR_INPADDR_ADDRESS)
		       ? RELOAD_FOR_OTHER_ADDRESS : RELOAD_OTHER);

		  /* Check to see if we accidentally converted two
		     reloads that use the same reload register with
		     different inputs to the same type.  If so, the
		     resulting code won't work.  */
		  if (rld[j].reg_rtx)
		    for (k = 0; k < j; k++)
		      gcc_assert (rld[k].in == 0 || rld[k].reg_rtx == 0
				  || rld[k].when_needed != rld[j].when_needed
				  || !rtx_equal_p (rld[k].reg_rtx,
						   rld[j].reg_rtx)
				  || rtx_equal_p (rld[k].in,
						  rld[j].in));
		}
	}
    }
}