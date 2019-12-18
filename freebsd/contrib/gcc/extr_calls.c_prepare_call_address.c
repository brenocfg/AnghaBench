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
 int /*<<< orphan*/  FUNCTION_MODE ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SMALL_REGISTER_CLASSES ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ convert_memory_address (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  flag_no_function_cse ; 
 scalar_t__ force_not_mem (scalar_t__) ; 
 scalar_t__ force_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ memory_address (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  static_chain_rtx ; 
 int /*<<< orphan*/  use_reg (scalar_t__*,int /*<<< orphan*/ ) ; 

rtx
prepare_call_address (rtx funexp, rtx static_chain_value,
		      rtx *call_fusage, int reg_parm_seen, int sibcallp)
{
  /* Make a valid memory address and copy constants through pseudo-regs,
     but not for a constant address if -fno-function-cse.  */
  if (GET_CODE (funexp) != SYMBOL_REF)
    /* If we are using registers for parameters, force the
       function address into a register now.  */
    funexp = ((SMALL_REGISTER_CLASSES && reg_parm_seen)
	      ? force_not_mem (memory_address (FUNCTION_MODE, funexp))
	      : memory_address (FUNCTION_MODE, funexp));
  else if (! sibcallp)
    {
#ifndef NO_FUNCTION_CSE
      if (optimize && ! flag_no_function_cse)
	funexp = force_reg (Pmode, funexp);
#endif
    }

  if (static_chain_value != 0)
    {
      static_chain_value = convert_memory_address (Pmode, static_chain_value);
      emit_move_insn (static_chain_rtx, static_chain_value);

      if (REG_P (static_chain_rtx))
	use_reg (call_fusage, static_chain_rtx);
    }

  return funexp;
}