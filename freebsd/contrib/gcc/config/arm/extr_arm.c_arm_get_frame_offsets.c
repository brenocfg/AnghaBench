#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct arm_stack_offsets {int saved_args; int frame; int saved_regs; int soft_frame; int outgoing_args; int locals_base; } ;
typedef  struct arm_stack_offsets arm_stack_offsets ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {struct arm_stack_offsets stack_offsets; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ ARM_DOUBLEWORD_ALIGN ; 
 int CALLER_INTERWORKING_SLOT_SIZE ; 
 unsigned int FIRST_FPA_REGNUM ; 
 unsigned int FIRST_IWMMXT_REGNUM ; 
 int /*<<< orphan*/  IS_VOLATILE (unsigned long) ; 
 unsigned int LAST_FPA_REGNUM ; 
 unsigned int LAST_IWMMXT_REGNUM ; 
 scalar_t__ ROUND_UP_WORD (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_ARM ; 
 scalar_t__ TARGET_BACKTRACE ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_REALLY_IWMMXT ; 
 scalar_t__ TARGET_VFP ; 
 int /*<<< orphan*/  arm_compute_save_reg_mask () ; 
 unsigned long arm_current_func_type () ; 
 scalar_t__ arm_get_vfp_saved_size () ; 
 int bit_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * call_used_regs ; 
 TYPE_2__* cfun ; 
 int current_function_outgoing_args_size ; 
 int current_function_pretend_args_size ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_frame_size () ; 
 int leaf_function_p () ; 
 scalar_t__* regs_ever_live ; 
 scalar_t__ reload_completed ; 
 int /*<<< orphan*/  thumb_compute_save_reg_mask () ; 

__attribute__((used)) static arm_stack_offsets *
arm_get_frame_offsets (void)
{
  struct arm_stack_offsets *offsets;
  unsigned long func_type;
  int leaf;
  int saved;
  HOST_WIDE_INT frame_size;

  offsets = &cfun->machine->stack_offsets;

  /* We need to know if we are a leaf function.  Unfortunately, it
     is possible to be called after start_sequence has been called,
     which causes get_insns to return the insns for the sequence,
     not the function, which will cause leaf_function_p to return
     the incorrect result.

     to know about leaf functions once reload has completed, and the
     frame size cannot be changed after that time, so we can safely
     use the cached value.  */

  if (reload_completed)
    return offsets;

  /* Initially this is the size of the local variables.  It will translated
     into an offset once we have determined the size of preceding data.  */
  frame_size = ROUND_UP_WORD (get_frame_size ());

  leaf = leaf_function_p ();

  /* Space for variadic functions.  */
  offsets->saved_args = current_function_pretend_args_size;

  offsets->frame = offsets->saved_args + (frame_pointer_needed ? 4 : 0);

  if (TARGET_ARM)
    {
      unsigned int regno;

      saved = bit_count (arm_compute_save_reg_mask ()) * 4;

      /* We know that SP will be doubleword aligned on entry, and we must
	 preserve that condition at any subroutine call.  We also require the
	 soft frame pointer to be doubleword aligned.  */

      if (TARGET_REALLY_IWMMXT)
	{
	  /* Check for the call-saved iWMMXt registers.  */
	  for (regno = FIRST_IWMMXT_REGNUM;
	       regno <= LAST_IWMMXT_REGNUM;
	       regno++)
	    if (regs_ever_live [regno] && ! call_used_regs [regno])
	      saved += 8;
	}

      func_type = arm_current_func_type ();
      if (! IS_VOLATILE (func_type))
	{
	  /* Space for saved FPA registers.  */
	  for (regno = FIRST_FPA_REGNUM; regno <= LAST_FPA_REGNUM; regno++)
	  if (regs_ever_live[regno] && ! call_used_regs[regno])
	    saved += 12;

	  /* Space for saved VFP registers.  */
	  if (TARGET_HARD_FLOAT && TARGET_VFP)
	    saved += arm_get_vfp_saved_size ();
	}
    }
  else /* TARGET_THUMB */
    {
      saved = bit_count (thumb_compute_save_reg_mask ()) * 4;
      if (TARGET_BACKTRACE)
	saved += 16;
    }

  /* Saved registers include the stack frame.  */
  offsets->saved_regs = offsets->saved_args + saved;
  offsets->soft_frame = offsets->saved_regs + CALLER_INTERWORKING_SLOT_SIZE;
  /* A leaf function does not need any stack alignment if it has nothing
     on the stack.  */
  if (leaf && frame_size == 0)
    {
      offsets->outgoing_args = offsets->soft_frame;
      offsets->locals_base = offsets->soft_frame;
      return offsets;
    }

  /* Ensure SFP has the correct alignment.  */
  if (ARM_DOUBLEWORD_ALIGN
      && (offsets->soft_frame & 7))
    offsets->soft_frame += 4;

  offsets->locals_base = offsets->soft_frame + frame_size;
  offsets->outgoing_args = (offsets->locals_base
			    + current_function_outgoing_args_size);

  if (ARM_DOUBLEWORD_ALIGN)
    {
      /* Ensure SP remains doubleword aligned.  */
      if (offsets->outgoing_args & 7)
	offsets->outgoing_args += 4;
      gcc_assert (!(offsets->outgoing_args & 7));
    }

  return offsets;
}