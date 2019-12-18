#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int icode; struct TYPE_9__* prev_sri; } ;
typedef  TYPE_2__ secondary_reload_info ;
typedef  scalar_t__ rtx ;
typedef  enum reload_type { ____Placeholder_reload_type } reload_type ;
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
struct TYPE_12__ {int n_operands; TYPE_1__* operand; } ;
struct TYPE_11__ {int secondary_p; int class; int inmode; int outmode; int secondary_in_reload; int secondary_out_reload; int secondary_in_icode; int secondary_out_icode; int when_needed; int opnum; int optional; int nocombine; scalar_t__ out_reg; scalar_t__ in_reg; scalar_t__ inc; scalar_t__ reg_rtx; scalar_t__ out; scalar_t__ in; } ;
struct TYPE_10__ {int (* secondary_reload ) (int,scalar_t__,int,int,TYPE_2__*) ;} ;
struct TYPE_8__ {char* constraint; int mode; } ;

/* Variables and functions */
 int CODE_FOR_nothing ; 
 size_t FIRST_PSEUDO_REGISTER ; 
 int GENERAL_REGS ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ MERGABLE_RELOADS (int,int,int,int) ; 
 scalar_t__ MERGE_TO_OTHER (int,int,int,int) ; 
 int MIN (int,int) ; 
 int NO_REGS ; 
 size_t REGNO (scalar_t__) ; 
 int REG_CLASS_FROM_CONSTRAINT (unsigned char,char const*) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int RELOAD_FOR_INPADDR_ADDRESS ; 
 int RELOAD_FOR_INPUT_ADDRESS ; 
 int RELOAD_FOR_OUTADDR_ADDRESS ; 
 int RELOAD_FOR_OUTPUT_ADDRESS ; 
 int RELOAD_OTHER ; 
 scalar_t__ SECONDARY_MEMORY_NEEDED (int,int,int) ; 
 scalar_t__ SMALL_REGISTER_CLASSES ; 
 scalar_t__ SMALL_REGISTER_CLASS_P (int) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_secondary_mem (scalar_t__,int,int,int) ; 
 TYPE_7__* insn_data ; 
 int n_reloads ; 
 scalar_t__ reg_class_subset_p (int,int) ; 
 scalar_t__* reg_equiv_mem ; 
 TYPE_5__* rld ; 
 int stub1 (int,scalar_t__,int,int,TYPE_2__*) ; 
 TYPE_3__ targetm ; 

__attribute__((used)) static int
push_secondary_reload (int in_p, rtx x, int opnum, int optional,
		       enum reg_class reload_class,
		       enum machine_mode reload_mode, enum reload_type type,
		       enum insn_code *picode, secondary_reload_info *prev_sri)
{
  enum reg_class class = NO_REGS;
  enum reg_class scratch_class;
  enum machine_mode mode = reload_mode;
  enum insn_code icode = CODE_FOR_nothing;
  enum insn_code t_icode = CODE_FOR_nothing;
  enum reload_type secondary_type;
  int s_reload, t_reload = -1;
  const char *scratch_constraint;
  char letter;
  secondary_reload_info sri;

  if (type == RELOAD_FOR_INPUT_ADDRESS
      || type == RELOAD_FOR_OUTPUT_ADDRESS
      || type == RELOAD_FOR_INPADDR_ADDRESS
      || type == RELOAD_FOR_OUTADDR_ADDRESS)
    secondary_type = type;
  else
    secondary_type = in_p ? RELOAD_FOR_INPUT_ADDRESS : RELOAD_FOR_OUTPUT_ADDRESS;

  *picode = CODE_FOR_nothing;

  /* If X is a paradoxical SUBREG, use the inner value to determine both the
     mode and object being reloaded.  */
  if (GET_CODE (x) == SUBREG
      && (GET_MODE_SIZE (GET_MODE (x))
	  > GET_MODE_SIZE (GET_MODE (SUBREG_REG (x)))))
    {
      x = SUBREG_REG (x);
      reload_mode = GET_MODE (x);
    }

  /* If X is a pseudo-register that has an equivalent MEM (actually, if it
     is still a pseudo-register by now, it *must* have an equivalent MEM
     but we don't want to assume that), use that equivalent when seeing if
     a secondary reload is needed since whether or not a reload is needed
     might be sensitive to the form of the MEM.  */

  if (REG_P (x) && REGNO (x) >= FIRST_PSEUDO_REGISTER
      && reg_equiv_mem[REGNO (x)] != 0)
    x = reg_equiv_mem[REGNO (x)];

  sri.icode = CODE_FOR_nothing;
  sri.prev_sri = prev_sri;
  class = targetm.secondary_reload (in_p, x, reload_class, reload_mode, &sri);
  icode = sri.icode;

  /* If we don't need any secondary registers, done.  */
  if (class == NO_REGS && icode == CODE_FOR_nothing)
    return -1;

  if (class != NO_REGS)
    t_reload = push_secondary_reload (in_p, x, opnum, optional, class,
				      reload_mode, type, &t_icode, &sri);

  /* If we will be using an insn, the secondary reload is for a
     scratch register.  */

  if (icode != CODE_FOR_nothing)
    {
      /* If IN_P is nonzero, the reload register will be the output in
	 operand 0.  If IN_P is zero, the reload register will be the input
	 in operand 1.  Outputs should have an initial "=", which we must
	 skip.  */

      /* ??? It would be useful to be able to handle only two, or more than
	 three, operands, but for now we can only handle the case of having
	 exactly three: output, input and one temp/scratch.  */
      gcc_assert (insn_data[(int) icode].n_operands == 3);

      /* ??? We currently have no way to represent a reload that needs
	 an icode to reload from an intermediate tertiary reload register.
	 We should probably have a new field in struct reload to tag a
	 chain of scratch operand reloads onto.   */
      gcc_assert (class == NO_REGS);

      scratch_constraint = insn_data[(int) icode].operand[2].constraint;
      gcc_assert (*scratch_constraint == '=');
      scratch_constraint++;
      if (*scratch_constraint == '&')
	scratch_constraint++;
      letter = *scratch_constraint;
      scratch_class = (letter == 'r' ? GENERAL_REGS
		       : REG_CLASS_FROM_CONSTRAINT ((unsigned char) letter,
						   scratch_constraint));

      class = scratch_class;
      mode = insn_data[(int) icode].operand[2].mode;
    }

  /* This case isn't valid, so fail.  Reload is allowed to use the same
     register for RELOAD_FOR_INPUT_ADDRESS and RELOAD_FOR_INPUT reloads, but
     in the case of a secondary register, we actually need two different
     registers for correct code.  We fail here to prevent the possibility of
     silently generating incorrect code later.

     The convention is that secondary input reloads are valid only if the
     secondary_class is different from class.  If you have such a case, you
     can not use secondary reloads, you must work around the problem some
     other way.

     Allow this when a reload_in/out pattern is being used.  I.e. assume
     that the generated code handles this case.  */

  gcc_assert (!in_p || class != reload_class || icode != CODE_FOR_nothing
	      || t_icode != CODE_FOR_nothing);

  /* See if we can reuse an existing secondary reload.  */
  for (s_reload = 0; s_reload < n_reloads; s_reload++)
    if (rld[s_reload].secondary_p
	&& (reg_class_subset_p (class, rld[s_reload].class)
	    || reg_class_subset_p (rld[s_reload].class, class))
	&& ((in_p && rld[s_reload].inmode == mode)
	    || (! in_p && rld[s_reload].outmode == mode))
	&& ((in_p && rld[s_reload].secondary_in_reload == t_reload)
	    || (! in_p && rld[s_reload].secondary_out_reload == t_reload))
	&& ((in_p && rld[s_reload].secondary_in_icode == t_icode)
	    || (! in_p && rld[s_reload].secondary_out_icode == t_icode))
	&& (SMALL_REGISTER_CLASS_P (class) || SMALL_REGISTER_CLASSES)
	&& MERGABLE_RELOADS (secondary_type, rld[s_reload].when_needed,
			     opnum, rld[s_reload].opnum))
      {
	if (in_p)
	  rld[s_reload].inmode = mode;
	if (! in_p)
	  rld[s_reload].outmode = mode;

	if (reg_class_subset_p (class, rld[s_reload].class))
	  rld[s_reload].class = class;

	rld[s_reload].opnum = MIN (rld[s_reload].opnum, opnum);
	rld[s_reload].optional &= optional;
	rld[s_reload].secondary_p = 1;
	if (MERGE_TO_OTHER (secondary_type, rld[s_reload].when_needed,
			    opnum, rld[s_reload].opnum))
	  rld[s_reload].when_needed = RELOAD_OTHER;
      }

  if (s_reload == n_reloads)
    {
#ifdef SECONDARY_MEMORY_NEEDED
      /* If we need a memory location to copy between the two reload regs,
	 set it up now.  Note that we do the input case before making
	 the reload and the output case after.  This is due to the
	 way reloads are output.  */

      if (in_p && icode == CODE_FOR_nothing
	  && SECONDARY_MEMORY_NEEDED (class, reload_class, mode))
	{
	  get_secondary_mem (x, reload_mode, opnum, type);

	  /* We may have just added new reloads.  Make sure we add
	     the new reload at the end.  */
	  s_reload = n_reloads;
	}
#endif

      /* We need to make a new secondary reload for this register class.  */
      rld[s_reload].in = rld[s_reload].out = 0;
      rld[s_reload].class = class;

      rld[s_reload].inmode = in_p ? mode : VOIDmode;
      rld[s_reload].outmode = ! in_p ? mode : VOIDmode;
      rld[s_reload].reg_rtx = 0;
      rld[s_reload].optional = optional;
      rld[s_reload].inc = 0;
      /* Maybe we could combine these, but it seems too tricky.  */
      rld[s_reload].nocombine = 1;
      rld[s_reload].in_reg = 0;
      rld[s_reload].out_reg = 0;
      rld[s_reload].opnum = opnum;
      rld[s_reload].when_needed = secondary_type;
      rld[s_reload].secondary_in_reload = in_p ? t_reload : -1;
      rld[s_reload].secondary_out_reload = ! in_p ? t_reload : -1;
      rld[s_reload].secondary_in_icode = in_p ? t_icode : CODE_FOR_nothing;
      rld[s_reload].secondary_out_icode
	= ! in_p ? t_icode : CODE_FOR_nothing;
      rld[s_reload].secondary_p = 1;

      n_reloads++;

#ifdef SECONDARY_MEMORY_NEEDED
      if (! in_p && icode == CODE_FOR_nothing
	  && SECONDARY_MEMORY_NEEDED (reload_class, class, mode))
	get_secondary_mem (x, mode, opnum, type);
#endif
    }

  *picode = icode;
  return s_reload;
}