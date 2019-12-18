#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct elims   TYPE_1__ ;

/* Type definitions */
struct elims {int const from; int const to; } ;

/* Variables and functions */
 size_t ARG_POINTER_REGNUM ; 
 size_t ARRAY_SIZE (TYPE_1__ const*) ; 
 TYPE_1__* ELIMINABLE_REGS ; 
 int const HARD_FRAME_POINTER_REGNUM ; 
 int /*<<< orphan*/  HAVE_nonlocal_goto ; 
 scalar_t__ HAVE_nonlocal_goto_receiver ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  cfun ; 
 int /*<<< orphan*/  copy_to_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* fixed_regs ; 
 int /*<<< orphan*/  gen_nonlocal_goto_receiver () ; 
 int /*<<< orphan*/  gen_rtx_ASM_INPUT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gen_rtx_CLOBBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_USE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_arg_pointer_save_area (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  static_chain_rtx ; 
 int /*<<< orphan*/  virtual_incoming_args_rtx ; 
 int /*<<< orphan*/  virtual_stack_vars_rtx ; 

__attribute__((used)) static void
expand_nl_goto_receiver (void)
{
  /* Clobber the FP when we get here, so we have to make sure it's
     marked as used by this function.  */
  emit_insn (gen_rtx_USE (VOIDmode, hard_frame_pointer_rtx));

  /* Mark the static chain as clobbered here so life information
     doesn't get messed up for it.  */
  emit_insn (gen_rtx_CLOBBER (VOIDmode, static_chain_rtx));

#ifdef HAVE_nonlocal_goto
  if (! HAVE_nonlocal_goto)
#endif
    /* First adjust our frame pointer to its actual value.  It was
       previously set to the start of the virtual area corresponding to
       the stacked variables when we branched here and now needs to be
       adjusted to the actual hardware fp value.

       Assignments are to virtual registers are converted by
       instantiate_virtual_regs into the corresponding assignment
       to the underlying register (fp in this case) that makes
       the original assignment true.
       So the following insn will actually be
       decrementing fp by STARTING_FRAME_OFFSET.  */
    emit_move_insn (virtual_stack_vars_rtx, hard_frame_pointer_rtx);

#if ARG_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM
  if (fixed_regs[ARG_POINTER_REGNUM])
    {
#ifdef ELIMINABLE_REGS
      /* If the argument pointer can be eliminated in favor of the
	 frame pointer, we don't need to restore it.  We assume here
	 that if such an elimination is present, it can always be used.
	 This is the case on all known machines; if we don't make this
	 assumption, we do unnecessary saving on many machines.  */
      static const struct elims {const int from, to;} elim_regs[] = ELIMINABLE_REGS;
      size_t i;

      for (i = 0; i < ARRAY_SIZE (elim_regs); i++)
	if (elim_regs[i].from == ARG_POINTER_REGNUM
	    && elim_regs[i].to == HARD_FRAME_POINTER_REGNUM)
	  break;

      if (i == ARRAY_SIZE (elim_regs))
#endif
	{
	  /* Now restore our arg pointer from the address at which it
	     was saved in our stack frame.  */
	  emit_move_insn (virtual_incoming_args_rtx,
			  copy_to_reg (get_arg_pointer_save_area (cfun)));
	}
    }
#endif

#ifdef HAVE_nonlocal_goto_receiver
  if (HAVE_nonlocal_goto_receiver)
    emit_insn (gen_nonlocal_goto_receiver ());
#endif

  /* @@@ This is a kludge.  Not all machine descriptions define a blockage
     insn, but we must not allow the code we just generated to be reordered
     by scheduling.  Specifically, the update of the frame pointer must
     happen immediately, not later.  So emit an ASM_INPUT to act as blockage
     insn.  */
  emit_insn (gen_rtx_ASM_INPUT (VOIDmode, ""));
}