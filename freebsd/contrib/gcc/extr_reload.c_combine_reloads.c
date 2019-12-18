#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
struct TYPE_10__ {TYPE_2__* rtl; } ;
struct TYPE_14__ {TYPE_3__ il; } ;
struct TYPE_13__ {int n_operands; TYPE_1__* operand; } ;
struct TYPE_12__ {int what; } ;
struct TYPE_11__ {scalar_t__ out; scalar_t__ in; scalar_t__ when_needed; size_t opnum; scalar_t__ class; size_t inmode; size_t outmode; scalar_t__ inc; scalar_t__ reg_rtx; int secondary_out_reload; int /*<<< orphan*/  secondary_out_icode; int /*<<< orphan*/  out_reg; int /*<<< orphan*/  nocombine; scalar_t__ optional; } ;
struct TYPE_9__ {int /*<<< orphan*/  global_live_at_end; } ;
struct TYPE_8__ {char* constraint; } ;

/* Variables and functions */
 scalar_t__ CLASS_MAX_NREGS (scalar_t__,size_t) ; 
 TYPE_7__* ENTRY_BLOCK_PTR ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 size_t GET_MODE (scalar_t__) ; 
 scalar_t__ HARD_REGNO_MODE_OK (size_t,size_t) ; 
 size_t INSN_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MATCHES (scalar_t__,scalar_t__) ; 
 scalar_t__ ORIGINAL_REGNO (scalar_t__) ; 
 size_t REGNO (scalar_t__) ; 
 scalar_t__ REG_DEAD ; 
 scalar_t__ REG_NOTES (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_NOTE_KIND (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ RELOAD_FOR_INPUT ; 
 scalar_t__ RELOAD_FOR_OUTADDR_ADDRESS ; 
 scalar_t__ RELOAD_FOR_OUTPUT ; 
 scalar_t__ RELOAD_FOR_OUTPUT_ADDRESS ; 
 scalar_t__ RELOAD_OTHER ; 
 scalar_t__ SMALL_REGISTER_CLASSES ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ earlyclobber_operand_p (scalar_t__) ; 
 int /*<<< orphan*/ * fixed_regs ; 
 scalar_t__ gen_rtx_REG (size_t,size_t) ; 
 scalar_t__** hard_regno_nregs ; 
 TYPE_6__* insn_data ; 
 int n_reloads ; 
 int n_replacements ; 
 int /*<<< orphan*/ * reg_class_contents ; 
 scalar_t__* reg_class_size ; 
 scalar_t__ reg_class_subset_p (scalar_t__,scalar_t__) ; 
 scalar_t__ reg_overlap_mentioned_for_reload_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  reload_inner_reg_of_subreg (scalar_t__,size_t,int) ; 
 TYPE_5__* replacements ; 
 TYPE_4__* rld ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__** secondary_memlocs_elim ; 
 int /*<<< orphan*/  this_insn ; 

__attribute__((used)) static void
combine_reloads (void)
{
  int i;
  int output_reload = -1;
  int secondary_out = -1;
  rtx note;

  /* Find the output reload; return unless there is exactly one
     and that one is mandatory.  */

  for (i = 0; i < n_reloads; i++)
    if (rld[i].out != 0)
      {
	if (output_reload >= 0)
	  return;
	output_reload = i;
      }

  if (output_reload < 0 || rld[output_reload].optional)
    return;

  /* An input-output reload isn't combinable.  */

  if (rld[output_reload].in != 0)
    return;

  /* If this reload is for an earlyclobber operand, we can't do anything.  */
  if (earlyclobber_operand_p (rld[output_reload].out))
    return;

  /* If there is a reload for part of the address of this operand, we would
     need to chnage it to RELOAD_FOR_OTHER_ADDRESS.  But that would extend
     its life to the point where doing this combine would not lower the
     number of spill registers needed.  */
  for (i = 0; i < n_reloads; i++)
    if ((rld[i].when_needed == RELOAD_FOR_OUTPUT_ADDRESS
	 || rld[i].when_needed == RELOAD_FOR_OUTADDR_ADDRESS)
	&& rld[i].opnum == rld[output_reload].opnum)
      return;

  /* Check each input reload; can we combine it?  */

  for (i = 0; i < n_reloads; i++)
    if (rld[i].in && ! rld[i].optional && ! rld[i].nocombine
	/* Life span of this reload must not extend past main insn.  */
	&& rld[i].when_needed != RELOAD_FOR_OUTPUT_ADDRESS
	&& rld[i].when_needed != RELOAD_FOR_OUTADDR_ADDRESS
	&& rld[i].when_needed != RELOAD_OTHER
	&& (CLASS_MAX_NREGS (rld[i].class, rld[i].inmode)
	    == CLASS_MAX_NREGS (rld[output_reload].class,
				rld[output_reload].outmode))
	&& rld[i].inc == 0
	&& rld[i].reg_rtx == 0
#ifdef SECONDARY_MEMORY_NEEDED
	/* Don't combine two reloads with different secondary
	   memory locations.  */
	&& (secondary_memlocs_elim[(int) rld[output_reload].outmode][rld[i].opnum] == 0
	    || secondary_memlocs_elim[(int) rld[output_reload].outmode][rld[output_reload].opnum] == 0
	    || rtx_equal_p (secondary_memlocs_elim[(int) rld[output_reload].outmode][rld[i].opnum],
			    secondary_memlocs_elim[(int) rld[output_reload].outmode][rld[output_reload].opnum]))
#endif
	&& (SMALL_REGISTER_CLASSES
	    ? (rld[i].class == rld[output_reload].class)
	    : (reg_class_subset_p (rld[i].class,
				   rld[output_reload].class)
	       || reg_class_subset_p (rld[output_reload].class,
				      rld[i].class)))
	&& (MATCHES (rld[i].in, rld[output_reload].out)
	    /* Args reversed because the first arg seems to be
	       the one that we imagine being modified
	       while the second is the one that might be affected.  */
	    || (! reg_overlap_mentioned_for_reload_p (rld[output_reload].out,
						      rld[i].in)
		/* However, if the input is a register that appears inside
		   the output, then we also can't share.
		   Imagine (set (mem (reg 69)) (plus (reg 69) ...)).
		   If the same reload reg is used for both reg 69 and the
		   result to be stored in memory, then that result
		   will clobber the address of the memory ref.  */
		&& ! (REG_P (rld[i].in)
		      && reg_overlap_mentioned_for_reload_p (rld[i].in,
							     rld[output_reload].out))))
	&& ! reload_inner_reg_of_subreg (rld[i].in, rld[i].inmode,
					 rld[i].when_needed != RELOAD_FOR_INPUT)
	&& (reg_class_size[(int) rld[i].class]
	    || SMALL_REGISTER_CLASSES)
	/* We will allow making things slightly worse by combining an
	   input and an output, but no worse than that.  */
	&& (rld[i].when_needed == RELOAD_FOR_INPUT
	    || rld[i].when_needed == RELOAD_FOR_OUTPUT))
      {
	int j;

	/* We have found a reload to combine with!  */
	rld[i].out = rld[output_reload].out;
	rld[i].out_reg = rld[output_reload].out_reg;
	rld[i].outmode = rld[output_reload].outmode;
	/* Mark the old output reload as inoperative.  */
	rld[output_reload].out = 0;
	/* The combined reload is needed for the entire insn.  */
	rld[i].when_needed = RELOAD_OTHER;
	/* If the output reload had a secondary reload, copy it.  */
	if (rld[output_reload].secondary_out_reload != -1)
	  {
	    rld[i].secondary_out_reload
	      = rld[output_reload].secondary_out_reload;
	    rld[i].secondary_out_icode
	      = rld[output_reload].secondary_out_icode;
	  }

#ifdef SECONDARY_MEMORY_NEEDED
	/* Copy any secondary MEM.  */
	if (secondary_memlocs_elim[(int) rld[output_reload].outmode][rld[output_reload].opnum] != 0)
	  secondary_memlocs_elim[(int) rld[output_reload].outmode][rld[i].opnum]
	    = secondary_memlocs_elim[(int) rld[output_reload].outmode][rld[output_reload].opnum];
#endif
	/* If required, minimize the register class.  */
	if (reg_class_subset_p (rld[output_reload].class,
				rld[i].class))
	  rld[i].class = rld[output_reload].class;

	/* Transfer all replacements from the old reload to the combined.  */
	for (j = 0; j < n_replacements; j++)
	  if (replacements[j].what == output_reload)
	    replacements[j].what = i;

	return;
      }

  /* If this insn has only one operand that is modified or written (assumed
     to be the first),  it must be the one corresponding to this reload.  It
     is safe to use anything that dies in this insn for that output provided
     that it does not occur in the output (we already know it isn't an
     earlyclobber.  If this is an asm insn, give up.  */

  if (INSN_CODE (this_insn) == -1)
    return;

  for (i = 1; i < insn_data[INSN_CODE (this_insn)].n_operands; i++)
    if (insn_data[INSN_CODE (this_insn)].operand[i].constraint[0] == '='
	|| insn_data[INSN_CODE (this_insn)].operand[i].constraint[0] == '+')
      return;

  /* See if some hard register that dies in this insn and is not used in
     the output is the right class.  Only works if the register we pick
     up can fully hold our output reload.  */
  for (note = REG_NOTES (this_insn); note; note = XEXP (note, 1))
    if (REG_NOTE_KIND (note) == REG_DEAD
	&& REG_P (XEXP (note, 0))
	&& ! reg_overlap_mentioned_for_reload_p (XEXP (note, 0),
						 rld[output_reload].out)
	&& REGNO (XEXP (note, 0)) < FIRST_PSEUDO_REGISTER
	&& HARD_REGNO_MODE_OK (REGNO (XEXP (note, 0)), rld[output_reload].outmode)
	&& TEST_HARD_REG_BIT (reg_class_contents[(int) rld[output_reload].class],
			      REGNO (XEXP (note, 0)))
	&& (hard_regno_nregs[REGNO (XEXP (note, 0))][rld[output_reload].outmode]
	    <= hard_regno_nregs[REGNO (XEXP (note, 0))][GET_MODE (XEXP (note, 0))])
	/* Ensure that a secondary or tertiary reload for this output
	   won't want this register.  */
	&& ((secondary_out = rld[output_reload].secondary_out_reload) == -1
	    || (! (TEST_HARD_REG_BIT
		   (reg_class_contents[(int) rld[secondary_out].class],
		    REGNO (XEXP (note, 0))))
		&& ((secondary_out = rld[secondary_out].secondary_out_reload) == -1
		    ||  ! (TEST_HARD_REG_BIT
			   (reg_class_contents[(int) rld[secondary_out].class],
			    REGNO (XEXP (note, 0)))))))
	&& ! fixed_regs[REGNO (XEXP (note, 0))]
	/* Check that we don't use a hardreg for an uninitialized
	   pseudo.  See also find_dummy_reload().  */
	&& (ORIGINAL_REGNO (XEXP (note, 0)) < FIRST_PSEUDO_REGISTER
	    || ! bitmap_bit_p (ENTRY_BLOCK_PTR->il.rtl->global_live_at_end,
			       ORIGINAL_REGNO (XEXP (note, 0)))))
      {
	rld[output_reload].reg_rtx
	  = gen_rtx_REG (rld[output_reload].outmode,
			 REGNO (XEXP (note, 0)));
	return;
      }
}