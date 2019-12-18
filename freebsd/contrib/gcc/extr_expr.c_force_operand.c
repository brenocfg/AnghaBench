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

/* Variables and functions */
 scalar_t__ ARITHMETIC_P (scalar_t__) ; 
#define  ASHIFTRT 142 
 scalar_t__ CONST ; 
 int /*<<< orphan*/  CONSTANT_P (scalar_t__) ; 
 scalar_t__ CONST_INT ; 
#define  DIV 141 
 scalar_t__ FIRST_VIRTUAL_REGISTER ; 
#define  FIX 140 
#define  FLOAT 139 
#define  FLOAT_EXTEND 138 
 int /*<<< orphan*/  FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
#define  FLOAT_TRUNCATE 137 
 int GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEGRAL_MODE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ LAST_VIRTUAL_REGISTER ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 int MINUS ; 
#define  MOD 136 
#define  MULT 135 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 int PLUS ; 
 int /*<<< orphan*/  RDIV_EXPR ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
#define  SIGN_EXTEND 134 
 int SUBREG ; 
 int /*<<< orphan*/  SUBREG_BYTE (scalar_t__) ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ SYMBOL_REF ; 
#define  TRUNCATE 133 
 int /*<<< orphan*/  TRUNC_DIV_EXPR ; 
 int /*<<< orphan*/  TRUNC_MOD_EXPR ; 
#define  UDIV 132 
#define  UMOD 131 
 scalar_t__ UNARY_P (scalar_t__) ; 
#define  UNSIGNED_FIX 130 
#define  UNSIGNED_FLOAT 129 
 scalar_t__ XEXP (scalar_t__,int) ; 
#define  ZERO_EXTEND 128 
 int /*<<< orphan*/  convert_move (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_divmod (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  expand_fix (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  expand_float (scalar_t__,scalar_t__,int) ; 
 scalar_t__ expand_mult (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ expand_simple_binop (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_simple_unop (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ get_subtarget (scalar_t__) ; 
 scalar_t__ negate_rtx (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pic_offset_table_rtx ; 
 scalar_t__ simplify_gen_subreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
force_operand (rtx value, rtx target)
{
  rtx op1, op2;
  /* Use subtarget as the target for operand 0 of a binary operation.  */
  rtx subtarget = get_subtarget (target);
  enum rtx_code code = GET_CODE (value);

  /* Check for subreg applied to an expression produced by loop optimizer.  */
  if (code == SUBREG
      && !REG_P (SUBREG_REG (value))
      && !MEM_P (SUBREG_REG (value)))
    {
      value = simplify_gen_subreg (GET_MODE (value),
				   force_reg (GET_MODE (SUBREG_REG (value)),
					      force_operand (SUBREG_REG (value),
							     NULL_RTX)),
				   GET_MODE (SUBREG_REG (value)),
				   SUBREG_BYTE (value));
      code = GET_CODE (value);
    }

  /* Check for a PIC address load.  */
  if ((code == PLUS || code == MINUS)
      && XEXP (value, 0) == pic_offset_table_rtx
      && (GET_CODE (XEXP (value, 1)) == SYMBOL_REF
	  || GET_CODE (XEXP (value, 1)) == LABEL_REF
	  || GET_CODE (XEXP (value, 1)) == CONST))
    {
      if (!subtarget)
	subtarget = gen_reg_rtx (GET_MODE (value));
      emit_move_insn (subtarget, value);
      return subtarget;
    }

  if (ARITHMETIC_P (value))
    {
      op2 = XEXP (value, 1);
      if (!CONSTANT_P (op2) && !(REG_P (op2) && op2 != subtarget))
	subtarget = 0;
      if (code == MINUS && GET_CODE (op2) == CONST_INT)
	{
	  code = PLUS;
	  op2 = negate_rtx (GET_MODE (value), op2);
	}

      /* Check for an addition with OP2 a constant integer and our first
         operand a PLUS of a virtual register and something else.  In that
         case, we want to emit the sum of the virtual register and the
         constant first and then add the other value.  This allows virtual
         register instantiation to simply modify the constant rather than
         creating another one around this addition.  */
      if (code == PLUS && GET_CODE (op2) == CONST_INT
	  && GET_CODE (XEXP (value, 0)) == PLUS
	  && REG_P (XEXP (XEXP (value, 0), 0))
	  && REGNO (XEXP (XEXP (value, 0), 0)) >= FIRST_VIRTUAL_REGISTER
	  && REGNO (XEXP (XEXP (value, 0), 0)) <= LAST_VIRTUAL_REGISTER)
	{
	  rtx temp = expand_simple_binop (GET_MODE (value), code,
					  XEXP (XEXP (value, 0), 0), op2,
					  subtarget, 0, OPTAB_LIB_WIDEN);
	  return expand_simple_binop (GET_MODE (value), code, temp,
				      force_operand (XEXP (XEXP (value,
								 0), 1), 0),
				      target, 0, OPTAB_LIB_WIDEN);
	}

      op1 = force_operand (XEXP (value, 0), subtarget);
      op2 = force_operand (op2, NULL_RTX);
      switch (code)
	{
	case MULT:
	  return expand_mult (GET_MODE (value), op1, op2, target, 1);
	case DIV:
	  if (!INTEGRAL_MODE_P (GET_MODE (value)))
	    return expand_simple_binop (GET_MODE (value), code, op1, op2,
					target, 1, OPTAB_LIB_WIDEN);
	  else
	    return expand_divmod (0,
				  FLOAT_MODE_P (GET_MODE (value))
				  ? RDIV_EXPR : TRUNC_DIV_EXPR,
				  GET_MODE (value), op1, op2, target, 0);
	  break;
	case MOD:
	  return expand_divmod (1, TRUNC_MOD_EXPR, GET_MODE (value), op1, op2,
				target, 0);
	  break;
	case UDIV:
	  return expand_divmod (0, TRUNC_DIV_EXPR, GET_MODE (value), op1, op2,
				target, 1);
	  break;
	case UMOD:
	  return expand_divmod (1, TRUNC_MOD_EXPR, GET_MODE (value), op1, op2,
				target, 1);
	  break;
	case ASHIFTRT:
	  return expand_simple_binop (GET_MODE (value), code, op1, op2,
				      target, 0, OPTAB_LIB_WIDEN);
	  break;
	default:
	  return expand_simple_binop (GET_MODE (value), code, op1, op2,
				      target, 1, OPTAB_LIB_WIDEN);
	}
    }
  if (UNARY_P (value))
    {
      if (!target)
	target = gen_reg_rtx (GET_MODE (value));
      op1 = force_operand (XEXP (value, 0), NULL_RTX);
      switch (code)
	{
	case ZERO_EXTEND:
	case SIGN_EXTEND:
	case TRUNCATE:
	case FLOAT_EXTEND:
	case FLOAT_TRUNCATE:
	  convert_move (target, op1, code == ZERO_EXTEND);
	  return target;

	case FIX:
	case UNSIGNED_FIX:
	  expand_fix (target, op1, code == UNSIGNED_FIX);
	  return target;

	case FLOAT:
	case UNSIGNED_FLOAT:
	  expand_float (target, op1, code == UNSIGNED_FLOAT);
	  return target;

	default:
	  return expand_simple_unop (GET_MODE (value), code, op1, target, 0);
	}
    }

#ifdef INSN_SCHEDULING
  /* On machines that have insn scheduling, we want all memory reference to be
     explicit, so we need to deal with such paradoxical SUBREGs.  */
  if (GET_CODE (value) == SUBREG && MEM_P (SUBREG_REG (value))
      && (GET_MODE_SIZE (GET_MODE (value))
	  > GET_MODE_SIZE (GET_MODE (SUBREG_REG (value)))))
    value
      = simplify_gen_subreg (GET_MODE (value),
			     force_reg (GET_MODE (SUBREG_REG (value)),
					force_operand (SUBREG_REG (value),
						       NULL_RTX)),
			     GET_MODE (SUBREG_REG (value)),
			     SUBREG_BYTE (value));
#endif

  return value;
}