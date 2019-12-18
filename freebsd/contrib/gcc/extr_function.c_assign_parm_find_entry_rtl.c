#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  constant; } ;
struct TYPE_7__ {int /*<<< orphan*/  constant; } ;
struct TYPE_10__ {TYPE_3__ offset; TYPE_2__ slot_offset; } ;
struct assign_parm_data_one {scalar_t__ promoted_mode; int named_arg; scalar_t__ passed_mode; int partial; scalar_t__ entry_parm; TYPE_5__ locate; int /*<<< orphan*/  passed_type; scalar_t__ stack_parm; } ;
struct assign_parm_data_all {scalar_t__ reg_parm_stack_space; int extra_pretend_bytes; int pretend_args_size; int /*<<< orphan*/  stack_args_size; int /*<<< orphan*/  args_so_far; } ;
typedef  scalar_t__ rtx ;
struct TYPE_6__ {int (* arg_partial_bytes ) (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ;scalar_t__ (* must_pass_in_stack ) (scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ (* pretend_outgoing_varargs_named ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {TYPE_1__ calls; } ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int CEIL_ROUND (int,int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_ARG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FUNCTION_INCOMING_ARG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STACK_BYTES ; 
 scalar_t__ VOIDmode ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  locate_and_pad_parm (scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (scalar_t__,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ targetm ; 

__attribute__((used)) static void
assign_parm_find_entry_rtl (struct assign_parm_data_all *all,
			    struct assign_parm_data_one *data)
{
  HOST_WIDE_INT pretend_bytes = 0;
  rtx entry_parm;
  bool in_regs;

  if (data->promoted_mode == VOIDmode)
    {
      data->entry_parm = data->stack_parm = const0_rtx;
      return;
    }

#ifdef FUNCTION_INCOMING_ARG
  entry_parm = FUNCTION_INCOMING_ARG (all->args_so_far, data->promoted_mode,
				      data->passed_type, data->named_arg);
#else
  entry_parm = FUNCTION_ARG (all->args_so_far, data->promoted_mode,
			     data->passed_type, data->named_arg);
#endif

  if (entry_parm == 0)
    data->promoted_mode = data->passed_mode;

  /* Determine parm's home in the stack, in case it arrives in the stack
     or we should pretend it did.  Compute the stack position and rtx where
     the argument arrives and its size.

     There is one complexity here:  If this was a parameter that would
     have been passed in registers, but wasn't only because it is
     __builtin_va_alist, we want locate_and_pad_parm to treat it as if
     it came in a register so that REG_PARM_STACK_SPACE isn't skipped.
     In this case, we call FUNCTION_ARG with NAMED set to 1 instead of 0
     as it was the previous time.  */
  in_regs = entry_parm != 0;
#ifdef STACK_PARMS_IN_REG_PARM_AREA
  in_regs = true;
#endif
  if (!in_regs && !data->named_arg)
    {
      if (targetm.calls.pretend_outgoing_varargs_named (&all->args_so_far))
	{
	  rtx tem;
#ifdef FUNCTION_INCOMING_ARG
	  tem = FUNCTION_INCOMING_ARG (all->args_so_far, data->promoted_mode,
				       data->passed_type, true);
#else
	  tem = FUNCTION_ARG (all->args_so_far, data->promoted_mode,
			      data->passed_type, true);
#endif
	  in_regs = tem != NULL;
	}
    }

  /* If this parameter was passed both in registers and in the stack, use
     the copy on the stack.  */
  if (targetm.calls.must_pass_in_stack (data->promoted_mode,
					data->passed_type))
    entry_parm = 0;

  if (entry_parm)
    {
      int partial;

      partial = targetm.calls.arg_partial_bytes (&all->args_so_far,
						 data->promoted_mode,
						 data->passed_type,
						 data->named_arg);
      data->partial = partial;

      /* The caller might already have allocated stack space for the
	 register parameters.  */
      if (partial != 0 && all->reg_parm_stack_space == 0)
	{
	  /* Part of this argument is passed in registers and part
	     is passed on the stack.  Ask the prologue code to extend
	     the stack part so that we can recreate the full value.

	     PRETEND_BYTES is the size of the registers we need to store.
	     CURRENT_FUNCTION_PRETEND_ARGS_SIZE is the amount of extra
	     stack space that the prologue should allocate.

	     Internally, gcc assumes that the argument pointer is aligned
	     to STACK_BOUNDARY bits.  This is used both for alignment
	     optimizations (see init_emit) and to locate arguments that are
	     aligned to more than PARM_BOUNDARY bits.  We must preserve this
	     invariant by rounding CURRENT_FUNCTION_PRETEND_ARGS_SIZE up to
	     a stack boundary.  */

	  /* We assume at most one partial arg, and it must be the first
	     argument on the stack.  */
	  gcc_assert (!all->extra_pretend_bytes && !all->pretend_args_size);

	  pretend_bytes = partial;
	  all->pretend_args_size = CEIL_ROUND (pretend_bytes, STACK_BYTES);

	  /* We want to align relative to the actual stack pointer, so
	     don't include this in the stack size until later.  */
	  all->extra_pretend_bytes = all->pretend_args_size;
	}
    }

  locate_and_pad_parm (data->promoted_mode, data->passed_type, in_regs,
		       entry_parm ? data->partial : 0, current_function_decl,
		       &all->stack_args_size, &data->locate);

  /* Adjust offsets to include the pretend args.  */
  pretend_bytes = all->extra_pretend_bytes - pretend_bytes;
  data->locate.slot_offset.constant += pretend_bytes;
  data->locate.offset.constant += pretend_bytes;

  data->entry_parm = entry_parm;
}