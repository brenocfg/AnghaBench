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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  BLKmode ; 
 int CEIL (int,int) ; 
 int FIRST_PSEUDO_REGISTER ; 
 int GET_MODE_ALIGNMENT (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ HAVE_untyped_return ; 
 int /*<<< orphan*/  INCOMING_REGNO (int) ; 
 int /*<<< orphan*/  Pmode ; 
 int VOIDmode ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int,int) ; 
 int* apply_result_mode ; 
 int /*<<< orphan*/  apply_result_size () ; 
 int /*<<< orphan*/  convert_memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  expand_naked_return () ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_USE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_untyped_return (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  push_to_sequence (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  result_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_builtin_return (rtx result)
{
  int size, align, regno;
  enum machine_mode mode;
  rtx reg;
  rtx call_fusage = 0;

  result = convert_memory_address (Pmode, result);

  apply_result_size ();
  result = gen_rtx_MEM (BLKmode, result);

#ifdef HAVE_untyped_return
  if (HAVE_untyped_return)
    {
      emit_jump_insn (gen_untyped_return (result, result_vector (0, result)));
      emit_barrier ();
      return;
    }
#endif

  /* Restore the return value and note that each value is used.  */
  size = 0;
  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
    if ((mode = apply_result_mode[regno]) != VOIDmode)
      {
	align = GET_MODE_ALIGNMENT (mode) / BITS_PER_UNIT;
	if (size % align != 0)
	  size = CEIL (size, align) * align;
	reg = gen_rtx_REG (mode, INCOMING_REGNO (regno));
	emit_move_insn (reg, adjust_address (result, mode, size));

	push_to_sequence (call_fusage);
	emit_insn (gen_rtx_USE (VOIDmode, reg));
	call_fusage = get_insns ();
	end_sequence ();
	size += GET_MODE_SIZE (mode);
      }

  /* Put the USE insns before the return.  */
  emit_insn (call_fusage);

  /* Return whatever values was restored by jumping directly to the end
     of the function.  */
  expand_naked_return ();
}