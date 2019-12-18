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
struct TYPE_4__ {scalar_t__ (* struct_value_rtx ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ calls; } ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int BLKmode ; 
 int /*<<< orphan*/  BLOCK_OP_NORMAL ; 
 int CEIL (int,int) ; 
 scalar_t__ CONST_INT ; 
 int FIRST_PSEUDO_REGISTER ; 
 int FUNCTION_MODE ; 
 int /*<<< orphan*/  GEN_CALL_VALUE (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 int GET_MODE_ALIGNMENT (int) ; 
 int GET_MODE_SIZE (int) ; 
 scalar_t__ HAVE_call_value ; 
 scalar_t__ HAVE_save_stack_nonlocal ; 
 scalar_t__ HAVE_untyped_call ; 
 int /*<<< orphan*/  INTVAL (scalar_t__) ; 
 int /*<<< orphan*/  MINUS ; 
 int /*<<< orphan*/  NO_DEFER_POP ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OK_DEFER_POP ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 int /*<<< orphan*/  PARM_BOUNDARY ; 
 int Pmode ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  SAVE_BLOCK ; 
 int /*<<< orphan*/  SAVE_NONLOCAL ; 
 scalar_t__ SYMBOL_REF ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_function_usage_to (scalar_t__,scalar_t__) ; 
 scalar_t__ adjust_address (scalar_t__,int,int) ; 
 int /*<<< orphan*/  allocate_dynamic_stack_space (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int* apply_args_mode ; 
 int /*<<< orphan*/  apply_args_size () ; 
 int* apply_result_mode ; 
 int /*<<< orphan*/  apply_result_size () ; 
 scalar_t__ assign_stack_local (int,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* cfun ; 
 int /*<<< orphan*/  const0_rtx ; 
 scalar_t__ convert_memory_address (int,scalar_t__) ; 
 scalar_t__ copy_addr_to_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 int /*<<< orphan*/  emit_block_move (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_call_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_stack_restore (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_stack_save (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_simple_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ gen_reg_rtx (int) ; 
 scalar_t__ gen_rtx_MEM (int,scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_REG (int,int) ; 
 int /*<<< orphan*/  gen_untyped_call (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ last_call_insn () ; 
 scalar_t__ memory_address (int,scalar_t__) ; 
 int /*<<< orphan*/  negate_rtx (int,scalar_t__) ; 
 scalar_t__ plus_constant (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ prepare_call_address (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ptr_mode ; 
 int /*<<< orphan*/  result_vector (int,scalar_t__) ; 
 int /*<<< orphan*/  set_mem_align (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 
 int /*<<< orphan*/  use_reg (scalar_t__*,scalar_t__) ; 
 scalar_t__ virtual_outgoing_args_rtx ; 

__attribute__((used)) static rtx
expand_builtin_apply (rtx function, rtx arguments, rtx argsize)
{
  int size, align, regno;
  enum machine_mode mode;
  rtx incoming_args, result, reg, dest, src, call_insn;
  rtx old_stack_level = 0;
  rtx call_fusage = 0;
  rtx struct_value = targetm.calls.struct_value_rtx (cfun ? TREE_TYPE (cfun->decl) : 0, 0);

  arguments = convert_memory_address (Pmode, arguments);

  /* Create a block where the return registers can be saved.  */
  result = assign_stack_local (BLKmode, apply_result_size (), -1);

  /* Fetch the arg pointer from the ARGUMENTS block.  */
  incoming_args = gen_reg_rtx (Pmode);
  emit_move_insn (incoming_args, gen_rtx_MEM (Pmode, arguments));
#ifndef STACK_GROWS_DOWNWARD
  incoming_args = expand_simple_binop (Pmode, MINUS, incoming_args, argsize,
				       incoming_args, 0, OPTAB_LIB_WIDEN);
#endif

  /* Push a new argument block and copy the arguments.  Do not allow
     the (potential) memcpy call below to interfere with our stack
     manipulations.  */
  do_pending_stack_adjust ();
  NO_DEFER_POP;

  /* Save the stack with nonlocal if available.  */
#ifdef HAVE_save_stack_nonlocal
  if (HAVE_save_stack_nonlocal)
    emit_stack_save (SAVE_NONLOCAL, &old_stack_level, NULL_RTX);
  else
#endif
    emit_stack_save (SAVE_BLOCK, &old_stack_level, NULL_RTX);

  /* Allocate a block of memory onto the stack and copy the memory
     arguments to the outgoing arguments address.  */
  allocate_dynamic_stack_space (argsize, 0, BITS_PER_UNIT);
  dest = virtual_outgoing_args_rtx;
#ifndef STACK_GROWS_DOWNWARD
  if (GET_CODE (argsize) == CONST_INT)
    dest = plus_constant (dest, -INTVAL (argsize));
  else
    dest = gen_rtx_PLUS (Pmode, dest, negate_rtx (Pmode, argsize));
#endif
  dest = gen_rtx_MEM (BLKmode, dest);
  set_mem_align (dest, PARM_BOUNDARY);
  src = gen_rtx_MEM (BLKmode, incoming_args);
  set_mem_align (src, PARM_BOUNDARY);
  emit_block_move (dest, src, argsize, BLOCK_OP_NORMAL);

  /* Refer to the argument block.  */
  apply_args_size ();
  arguments = gen_rtx_MEM (BLKmode, arguments);
  set_mem_align (arguments, PARM_BOUNDARY);

  /* Walk past the arg-pointer and structure value address.  */
  size = GET_MODE_SIZE (Pmode);
  if (struct_value)
    size += GET_MODE_SIZE (Pmode);

  /* Restore each of the registers previously saved.  Make USE insns
     for each of these registers for use in making the call.  */
  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
    if ((mode = apply_args_mode[regno]) != VOIDmode)
      {
	align = GET_MODE_ALIGNMENT (mode) / BITS_PER_UNIT;
	if (size % align != 0)
	  size = CEIL (size, align) * align;
	reg = gen_rtx_REG (mode, regno);
	emit_move_insn (reg, adjust_address (arguments, mode, size));
	use_reg (&call_fusage, reg);
	size += GET_MODE_SIZE (mode);
      }

  /* Restore the structure value address unless this is passed as an
     "invisible" first argument.  */
  size = GET_MODE_SIZE (Pmode);
  if (struct_value)
    {
      rtx value = gen_reg_rtx (Pmode);
      emit_move_insn (value, adjust_address (arguments, Pmode, size));
      emit_move_insn (struct_value, value);
      if (REG_P (struct_value))
	use_reg (&call_fusage, struct_value);
      size += GET_MODE_SIZE (Pmode);
    }

  /* All arguments and registers used for the call are set up by now!  */
  function = prepare_call_address (function, NULL, &call_fusage, 0, 0);

  /* Ensure address is valid.  SYMBOL_REF is already valid, so no need,
     and we don't want to load it into a register as an optimization,
     because prepare_call_address already did it if it should be done.  */
  if (GET_CODE (function) != SYMBOL_REF)
    function = memory_address (FUNCTION_MODE, function);

  /* Generate the actual call instruction and save the return value.  */
#ifdef HAVE_untyped_call
  if (HAVE_untyped_call)
    emit_call_insn (gen_untyped_call (gen_rtx_MEM (FUNCTION_MODE, function),
				      result, result_vector (1, result)));
  else
#endif
#ifdef HAVE_call_value
  if (HAVE_call_value)
    {
      rtx valreg = 0;

      /* Locate the unique return register.  It is not possible to
	 express a call that sets more than one return register using
	 call_value; use untyped_call for that.  In fact, untyped_call
	 only needs to save the return registers in the given block.  */
      for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
	if ((mode = apply_result_mode[regno]) != VOIDmode)
	  {
	    gcc_assert (!valreg); /* HAVE_untyped_call required.  */

	    valreg = gen_rtx_REG (mode, regno);
	  }

      emit_call_insn (GEN_CALL_VALUE (valreg,
				      gen_rtx_MEM (FUNCTION_MODE, function),
				      const0_rtx, NULL_RTX, const0_rtx));

      emit_move_insn (adjust_address (result, GET_MODE (valreg), 0), valreg);
    }
  else
#endif
    gcc_unreachable ();

  /* Find the CALL insn we just emitted, and attach the register usage
     information.  */
  call_insn = last_call_insn ();
  add_function_usage_to (call_insn, call_fusage);

  /* Restore the stack.  */
#ifdef HAVE_save_stack_nonlocal
  if (HAVE_save_stack_nonlocal)
    emit_stack_restore (SAVE_NONLOCAL, old_stack_level, NULL_RTX);
  else
#endif
    emit_stack_restore (SAVE_BLOCK, old_stack_level, NULL_RTX);

  OK_DEFER_POP;

  /* Return the address of the result block.  */
  result = copy_addr_to_reg (XEXP (result, 0));
  return convert_memory_address (ptr_mode, result);
}