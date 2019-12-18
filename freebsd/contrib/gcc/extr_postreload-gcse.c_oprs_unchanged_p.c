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
#define  ADDR_DIFF_VEC 145 
#define  ADDR_VEC 144 
#define  CC0 143 
#define  CONST 142 
#define  CONST_DOUBLE 141 
#define  CONST_INT 140 
#define  CONST_VECTOR 139 
 int /*<<< orphan*/  FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int /*<<< orphan*/  INSN_CUID (scalar_t__) ; 
#define  LABEL_REF 138 
#define  MEM 137 
#define  PC 136 
#define  POST_DEC 135 
#define  POST_INC 134 
#define  POST_MODIFY 133 
#define  PRE_DEC 132 
#define  PRE_INC 131 
#define  PRE_MODIFY 130 
#define  REG 129 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
#define  SYMBOL_REF 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  load_killed_in_block_p (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  reg_changed_after_insn_p (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
oprs_unchanged_p (rtx x, rtx insn, bool after_insn)
{
  int i, j;
  enum rtx_code code;
  const char *fmt;

  if (x == 0)
    return 1;

  code = GET_CODE (x);
  switch (code)
    {
    case REG:
      /* We are called after register allocation.  */
      gcc_assert (REGNO (x) < FIRST_PSEUDO_REGISTER);
      if (after_insn)
	return !reg_changed_after_insn_p (x, INSN_CUID (insn) - 1);
      else
	return !reg_changed_after_insn_p (x, 0);

    case MEM:
      if (load_killed_in_block_p (INSN_CUID (insn), x, after_insn))
	return 0;
      else
	return oprs_unchanged_p (XEXP (x, 0), insn, after_insn);

    case PC:
    case CC0: /*FIXME*/
    case CONST:
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case SYMBOL_REF:
    case LABEL_REF:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
      return 1;

    case PRE_DEC:
    case PRE_INC:
    case POST_DEC:
    case POST_INC:
    case PRE_MODIFY:
    case POST_MODIFY:
      if (after_insn)
	return 0;
      break;

    default:
      break;
    }

  for (i = GET_RTX_LENGTH (code) - 1, fmt = GET_RTX_FORMAT (code); i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  if (! oprs_unchanged_p (XEXP (x, i), insn, after_insn))
	    return 0;
	}
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  if (! oprs_unchanged_p (XVECEXP (x, i, j), insn, after_insn))
	    return 0;
    }

  return 1;
}