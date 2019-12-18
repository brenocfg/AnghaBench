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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  INTVAL (scalar_t__) ; 
 scalar_t__ MINUS ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 scalar_t__ PLUS ; 
#define  POST_DEC 133 
#define  POST_INC 132 
#define  POST_MODIFY 131 
#define  PRE_DEC 130 
#define  PRE_INC 129 
#define  PRE_MODIFY 128 
 int /*<<< orphan*/  PUSH_ROUNDING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_simple_binop (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ plus_constant (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ replace_equiv_address (scalar_t__,scalar_t__) ; 
 scalar_t__ stack_pointer_rtx ; 

__attribute__((used)) static rtx
emit_move_resolve_push (enum machine_mode mode, rtx x)
{
  enum rtx_code code = GET_CODE (XEXP (x, 0));
  HOST_WIDE_INT adjust;
  rtx temp;

  adjust = GET_MODE_SIZE (mode);
#ifdef PUSH_ROUNDING
  adjust = PUSH_ROUNDING (adjust);
#endif
  if (code == PRE_DEC || code == POST_DEC)
    adjust = -adjust;
  else if (code == PRE_MODIFY || code == POST_MODIFY)
    {
      rtx expr = XEXP (XEXP (x, 0), 1);
      HOST_WIDE_INT val;

      gcc_assert (GET_CODE (expr) == PLUS || GET_CODE (expr) == MINUS);
      gcc_assert (GET_CODE (XEXP (expr, 1)) == CONST_INT);
      val = INTVAL (XEXP (expr, 1));
      if (GET_CODE (expr) == MINUS)
	val = -val;
      gcc_assert (adjust == val || adjust == -val);
      adjust = val;
    }

  /* Do not use anti_adjust_stack, since we don't want to update
     stack_pointer_delta.  */
  temp = expand_simple_binop (Pmode, PLUS, stack_pointer_rtx,
			      GEN_INT (adjust), stack_pointer_rtx,
			      0, OPTAB_LIB_WIDEN);
  if (temp != stack_pointer_rtx)
    emit_move_insn (stack_pointer_rtx, temp);

  switch (code)
    {
    case PRE_INC:
    case PRE_DEC:
    case PRE_MODIFY:
      temp = stack_pointer_rtx;
      break;
    case POST_INC:
    case POST_DEC:
    case POST_MODIFY:
      temp = plus_constant (stack_pointer_rtx, -adjust);
      break;
    default:
      gcc_unreachable ();
    }

  return replace_equiv_address (x, temp);
}