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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  NEXT_INSN (int /*<<< orphan*/ ) ; 
 scalar_t__ apply_args_value ; 
 int /*<<< orphan*/  emit_insn_before (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  entry_of_function () ; 
 scalar_t__ expand_builtin_apply_args_1 () ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  pop_topmost_sequence () ; 
 int /*<<< orphan*/  push_topmost_sequence () ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static rtx
expand_builtin_apply_args (void)
{
  /* Don't do __builtin_apply_args more than once in a function.
     Save the result of the first call and reuse it.  */
  if (apply_args_value != 0)
    return apply_args_value;
  {
    /* When this function is called, it means that registers must be
       saved on entry to this function.  So we migrate the
       call to the first insn of this function.  */
    rtx temp;
    rtx seq;

    start_sequence ();
    temp = expand_builtin_apply_args_1 ();
    seq = get_insns ();
    end_sequence ();

    apply_args_value = temp;

    /* Put the insns after the NOTE that starts the function.
       If this is inside a start_sequence, make the outer-level insn
       chain current, so the code is placed at the start of the
       function.  */
    push_topmost_sequence ();
    emit_insn_before (seq, NEXT_INSN (entry_of_function ()));
    pop_topmost_sequence ();
    return temp;
  }
}