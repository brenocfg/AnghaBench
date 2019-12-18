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

/* Variables and functions */
#define  AND 150 
#define  ASHIFTRT 149 
#define  CONST_DOUBLE 148 
 int CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
#define  CONST_INT 147 
#define  EQ 146 
#define  GE 145 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
#define  GEU 144 
#define  GT 143 
#define  GTU 142 
#define  HIGH 141 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  IOR 140 
#define  LE 139 
#define  LEU 138 
#define  LO_SUM 137 
#define  LSHIFTRT 136 
#define  LT 135 
#define  LTU 134 
#define  MEM 133 
#define  NE 132 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
#define  REG 131 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
#define  SIGN_EXTEND 130 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
#define  XOR 129 
#define  ZERO_EXTEND 128 
 int sparc_check_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_extends (rtx insn)
{
  register rtx pat = PATTERN (insn);

  switch (GET_CODE (SET_SRC (pat)))
    {
      /* Load and some shift instructions zero extend.  */
    case MEM:
    case ZERO_EXTEND:
      /* sethi clears the high bits */
    case HIGH:
      /* LO_SUM is used with sethi.  sethi cleared the high
	 bits and the values used with lo_sum are positive */
    case LO_SUM:
      /* Store flag stores 0 or 1 */
    case LT: case LTU:
    case GT: case GTU:
    case LE: case LEU:
    case GE: case GEU:
    case EQ:
    case NE:
      return 1;
    case AND:
      {
	rtx op0 = XEXP (SET_SRC (pat), 0);
	rtx op1 = XEXP (SET_SRC (pat), 1);
	if (GET_CODE (op1) == CONST_INT)
	  return INTVAL (op1) >= 0;
	if (GET_CODE (op0) != REG)
	  return 0;
	if (sparc_check_64 (op0, insn) == 1)
	  return 1;
	return (GET_CODE (op1) == REG && sparc_check_64 (op1, insn) == 1);
      }
    case IOR:
    case XOR:
      {
	rtx op0 = XEXP (SET_SRC (pat), 0);
	rtx op1 = XEXP (SET_SRC (pat), 1);
	if (GET_CODE (op0) != REG || sparc_check_64 (op0, insn) <= 0)
	  return 0;
	if (GET_CODE (op1) == CONST_INT)
	  return INTVAL (op1) >= 0;
	return (GET_CODE (op1) == REG && sparc_check_64 (op1, insn) == 1);
      }
    case LSHIFTRT:
      return GET_MODE (SET_SRC (pat)) == SImode;
      /* Positive integers leave the high bits zero.  */
    case CONST_DOUBLE:
      return ! (CONST_DOUBLE_LOW (SET_SRC (pat)) & 0x80000000);
    case CONST_INT:
      return ! (INTVAL (SET_SRC (pat)) & 0x80000000);
    case ASHIFTRT:
    case SIGN_EXTEND:
      return - (GET_MODE (SET_SRC (pat)) == SImode);
    case REG:
      return sparc_check_64 (SET_SRC (pat), insn);
    default:
      return 0;
    }
}