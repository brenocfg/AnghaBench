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
struct function {int /*<<< orphan*/  arg_pointer_save_area_init; scalar_t__ x_arg_pointer_save_area; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ assign_stack_local_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct function*) ; 
 struct function* cfun ; 
 int /*<<< orphan*/  emit_insn_after (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  entry_of_function () ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  pop_topmost_sequence () ; 
 int /*<<< orphan*/  push_topmost_sequence () ; 
 int /*<<< orphan*/  start_sequence () ; 
 int /*<<< orphan*/  validize_mem (scalar_t__) ; 
 int /*<<< orphan*/  virtual_incoming_args_rtx ; 

rtx
get_arg_pointer_save_area (struct function *f)
{
  rtx ret = f->x_arg_pointer_save_area;

  if (! ret)
    {
      ret = assign_stack_local_1 (Pmode, GET_MODE_SIZE (Pmode), 0, f);
      f->x_arg_pointer_save_area = ret;
    }

  if (f == cfun && ! f->arg_pointer_save_area_init)
    {
      rtx seq;

      /* Save the arg pointer at the beginning of the function.  The
	 generated stack slot may not be a valid memory address, so we
	 have to check it and fix it if necessary.  */
      start_sequence ();
      emit_move_insn (validize_mem (ret), virtual_incoming_args_rtx);
      seq = get_insns ();
      end_sequence ();

      push_topmost_sequence ();
      emit_insn_after (seq, entry_of_function ());
      pop_topmost_sequence ();
    }

  return ret;
}