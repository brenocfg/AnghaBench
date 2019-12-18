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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int /*<<< orphan*/  (* builtin_setjmp_frame_value ) () ;} ;

/* Variables and functions */
 int GET_MODE_SIZE (int) ; 
 scalar_t__ HAVE_builtin_setjmp_setup ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int Pmode ; 
 int /*<<< orphan*/  SAVE_NONLOCAL ; 
 int STACK_SAVEAREA_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_memory_address (int,int /*<<< orphan*/ ) ; 
 int current_function_calls_setjmp ; 
 int current_function_has_nonlocal_label ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_stack_save (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_builtin_setjmp_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LABEL_REF (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int,int /*<<< orphan*/ ) ; 
 int new_alias_set () ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_mem_alias_set (int /*<<< orphan*/ ,int) ; 
 int setjmp_alias_set ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__ targetm ; 
 int /*<<< orphan*/  validize_mem (int /*<<< orphan*/ ) ; 

void
expand_builtin_setjmp_setup (rtx buf_addr, rtx receiver_label)
{
  enum machine_mode sa_mode = STACK_SAVEAREA_MODE (SAVE_NONLOCAL);
  rtx stack_save;
  rtx mem;

  if (setjmp_alias_set == -1)
    setjmp_alias_set = new_alias_set ();

  buf_addr = convert_memory_address (Pmode, buf_addr);

  buf_addr = force_reg (Pmode, force_operand (buf_addr, NULL_RTX));

  /* We store the frame pointer and the address of receiver_label in
     the buffer and use the rest of it for the stack save area, which
     is machine-dependent.  */

  mem = gen_rtx_MEM (Pmode, buf_addr);
  set_mem_alias_set (mem, setjmp_alias_set);
  emit_move_insn (mem, targetm.builtin_setjmp_frame_value ());

  mem = gen_rtx_MEM (Pmode, plus_constant (buf_addr, GET_MODE_SIZE (Pmode))),
  set_mem_alias_set (mem, setjmp_alias_set);

  emit_move_insn (validize_mem (mem),
		  force_reg (Pmode, gen_rtx_LABEL_REF (Pmode, receiver_label)));

  stack_save = gen_rtx_MEM (sa_mode,
			    plus_constant (buf_addr,
					   2 * GET_MODE_SIZE (Pmode)));
  set_mem_alias_set (stack_save, setjmp_alias_set);
  emit_stack_save (SAVE_NONLOCAL, &stack_save, NULL_RTX);

  /* If there is further processing to do, do it.  */
#ifdef HAVE_builtin_setjmp_setup
  if (HAVE_builtin_setjmp_setup)
    emit_insn (gen_builtin_setjmp_setup (buf_addr));
#endif

  /* Tell optimize_save_area_alloca that extra work is going to
     need to go on during alloca.  */
  current_function_calls_setjmp = 1;

  /* Set this so all the registers get saved in our frame; we need to be
     able to copy the saved values for any registers from frames we unwind.  */
  current_function_has_nonlocal_label = 1;
}