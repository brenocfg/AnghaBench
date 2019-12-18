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
#define  ABS 159 
#define  ASM_INPUT 158 
#define  ASM_OPERANDS 157 
#define  CC0 156 
#define  COMPARE 155 
#define  CONST 154 
 int /*<<< orphan*/  CONSTANT_P (scalar_t__) ; 
#define  CONST_DOUBLE 153 
#define  CONST_INT 152 
#define  CONST_VECTOR 151 
#define  DIV 150 
#define  EQ 149 
#define  EXPR_LIST 148 
#define  FIX 147 
#define  GE 146 
 int GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  GT 145 
 int /*<<< orphan*/  HONOR_NANS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HONOR_SNANS (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 144 
#define  LE 143 
#define  LT 142 
#define  LTGT 141 
#define  MEM 140 
 int /*<<< orphan*/  MEM_NOTRAP_P (scalar_t__) ; 
 int MEM_VOLATILE_P (scalar_t__) ; 
#define  MOD 139 
 unsigned int MTP_AFTER_MOVE ; 
 unsigned int MTP_UNALIGNED_MEMS ; 
#define  NE 138 
#define  NEG 137 
#define  PC 136 
#define  REG 135 
 int /*<<< orphan*/  SCALAR_FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
#define  SCRATCH 134 
 int /*<<< orphan*/  STRICT_ALIGNMENT ; 
#define  SUBREG 133 
#define  SYMBOL_REF 132 
#define  TRAP_IF 131 
#define  UDIV 130 
#define  UMOD 129 
#define  UNSPEC_VOLATILE 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 scalar_t__ const0_rtx ; 
 int flag_trapping_math ; 
 int rtx_addr_can_trap_p_1 (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
may_trap_p_1 (rtx x, unsigned flags)
{
  int i;
  enum rtx_code code;
  const char *fmt;
  bool unaligned_mems = (flags & MTP_UNALIGNED_MEMS) != 0;

  if (x == 0)
    return 0;
  code = GET_CODE (x);
  switch (code)
    {
      /* Handle these cases quickly.  */
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case SYMBOL_REF:
    case LABEL_REF:
    case CONST:
    case PC:
    case CC0:
    case REG:
    case SCRATCH:
      return 0;

    case ASM_INPUT:
    case UNSPEC_VOLATILE:
    case TRAP_IF:
      return 1;

    case ASM_OPERANDS:
      return MEM_VOLATILE_P (x);

      /* Memory ref can trap unless it's a static var or a stack slot.  */
    case MEM:
      if (/* MEM_NOTRAP_P only relates to the actual position of the memory
	     reference; moving it out of condition might cause its address
	     become invalid.  */
	  !(flags & MTP_AFTER_MOVE)
	  && MEM_NOTRAP_P (x)
	  && (!STRICT_ALIGNMENT || !unaligned_mems))
	return 0;
      return
	rtx_addr_can_trap_p_1 (XEXP (x, 0), GET_MODE (x), unaligned_mems);

      /* Division by a non-constant might trap.  */
    case DIV:
    case MOD:
    case UDIV:
    case UMOD:
      if (HONOR_SNANS (GET_MODE (x)))
	return 1;
      if (SCALAR_FLOAT_MODE_P (GET_MODE (x)))
	return flag_trapping_math;
      if (!CONSTANT_P (XEXP (x, 1)) || (XEXP (x, 1) == const0_rtx))
	return 1;
      break;

    case EXPR_LIST:
      /* An EXPR_LIST is used to represent a function call.  This
	 certainly may trap.  */
      return 1;

    case GE:
    case GT:
    case LE:
    case LT:
    case LTGT:
    case COMPARE:
      /* Some floating point comparisons may trap.  */
      if (!flag_trapping_math)
	break;
      /* ??? There is no machine independent way to check for tests that trap
	 when COMPARE is used, though many targets do make this distinction.
	 For instance, sparc uses CCFPE for compares which generate exceptions
	 and CCFP for compares which do not generate exceptions.  */
      if (HONOR_NANS (GET_MODE (x)))
	return 1;
      /* But often the compare has some CC mode, so check operand
	 modes as well.  */
      if (HONOR_NANS (GET_MODE (XEXP (x, 0)))
	  || HONOR_NANS (GET_MODE (XEXP (x, 1))))
	return 1;
      break;

    case EQ:
    case NE:
      if (HONOR_SNANS (GET_MODE (x)))
	return 1;
      /* Often comparison is CC mode, so check operand modes.  */
      if (HONOR_SNANS (GET_MODE (XEXP (x, 0)))
	  || HONOR_SNANS (GET_MODE (XEXP (x, 1))))
	return 1;
      break;

    case FIX:
      /* Conversion of floating point might trap.  */
      if (flag_trapping_math && HONOR_NANS (GET_MODE (XEXP (x, 0))))
	return 1;
      break;

    case NEG:
    case ABS:
    case SUBREG:
      /* These operations don't trap even with floating point.  */
      break;

    default:
      /* Any floating arithmetic may trap.  */
      if (SCALAR_FLOAT_MODE_P (GET_MODE (x))
	  && flag_trapping_math)
	return 1;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  if (may_trap_p_1 (XEXP (x, i), flags))
	    return 1;
	}
      else if (fmt[i] == 'E')
	{
	  int j;
	  for (j = 0; j < XVECLEN (x, i); j++)
	    if (may_trap_p_1 (XVECEXP (x, i, j), flags))
	      return 1;
	}
    }
  return 0;
}