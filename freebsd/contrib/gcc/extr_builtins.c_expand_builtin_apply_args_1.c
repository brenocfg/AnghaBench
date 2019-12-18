#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_6__ {int /*<<< orphan*/  decl; } ;
struct TYPE_4__ {scalar_t__ (* struct_value_rtx ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {TYPE_1__ calls; } ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  BLKmode ; 
 int CEIL (int,int) ; 
 int FIRST_PSEUDO_REGISTER ; 
 int GET_MODE_ALIGNMENT (int) ; 
 int GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  INCOMING_REGNO (int) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int Pmode ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_address (scalar_t__,int,int) ; 
 int* apply_args_mode ; 
 int /*<<< orphan*/  apply_args_size () ; 
 scalar_t__ assign_stack_local (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* cfun ; 
 scalar_t__ copy_addr_to_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_to_reg (scalar_t__) ; 
 int /*<<< orphan*/  current_function_pretend_args_size ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ force_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ targetm ; 
 scalar_t__ virtual_incoming_args_rtx ; 

__attribute__((used)) static rtx
expand_builtin_apply_args_1 (void)
{
  rtx registers, tem;
  int size, align, regno;
  enum machine_mode mode;
  rtx struct_incoming_value = targetm.calls.struct_value_rtx (cfun ? TREE_TYPE (cfun->decl) : 0, 1);

  /* Create a block where the arg-pointer, structure value address,
     and argument registers can be saved.  */
  registers = assign_stack_local (BLKmode, apply_args_size (), -1);

  /* Walk past the arg-pointer and structure value address.  */
  size = GET_MODE_SIZE (Pmode);
  if (targetm.calls.struct_value_rtx (cfun ? TREE_TYPE (cfun->decl) : 0, 0))
    size += GET_MODE_SIZE (Pmode);

  /* Save each register used in calling a function to the block.  */
  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
    if ((mode = apply_args_mode[regno]) != VOIDmode)
      {
	align = GET_MODE_ALIGNMENT (mode) / BITS_PER_UNIT;
	if (size % align != 0)
	  size = CEIL (size, align) * align;

	tem = gen_rtx_REG (mode, INCOMING_REGNO (regno));

	emit_move_insn (adjust_address (registers, mode, size), tem);
	size += GET_MODE_SIZE (mode);
      }

  /* Save the arg pointer to the block.  */
  tem = copy_to_reg (virtual_incoming_args_rtx);
#ifdef STACK_GROWS_DOWNWARD
  /* We need the pointer as the caller actually passed them to us, not
     as we might have pretended they were passed.  Make sure it's a valid
     operand, as emit_move_insn isn't expected to handle a PLUS.  */
  tem
    = force_operand (plus_constant (tem, current_function_pretend_args_size),
		     NULL_RTX);
#endif
  emit_move_insn (adjust_address (registers, Pmode, 0), tem);

  size = GET_MODE_SIZE (Pmode);

  /* Save the structure value address unless this is passed as an
     "invisible" first argument.  */
  if (struct_incoming_value)
    {
      emit_move_insn (adjust_address (registers, Pmode, size),
		      copy_to_reg (struct_incoming_value));
      size += GET_MODE_SIZE (Pmode);
    }

  /* Return the address of the block.  */
  return copy_addr_to_reg (XEXP (registers, 0));
}