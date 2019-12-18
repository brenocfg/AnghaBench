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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  CC0 137 
#define  CONST 136 
#define  CONST_DOUBLE 135 
#define  CONST_INT 134 
#define  CONST_VECTOR 133 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  LABEL_REF 132 
#define  MEM 131 
 int /*<<< orphan*/  MEM_READONLY_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT_INSN (int /*<<< orphan*/ ) ; 
#define  PC 130 
#define  REG 129 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memory_modified_in_insn_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reg_set_between_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
modified_between_p (rtx x, rtx start, rtx end)
{
  enum rtx_code code = GET_CODE (x);
  const char *fmt;
  int i, j;
  rtx insn;

  if (start == end)
    return 0;

  switch (code)
    {
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case CONST:
    case SYMBOL_REF:
    case LABEL_REF:
      return 0;

    case PC:
    case CC0:
      return 1;

    case MEM:
      if (modified_between_p (XEXP (x, 0), start, end))
	return 1;
      if (MEM_READONLY_P (x))
	return 0;
      for (insn = NEXT_INSN (start); insn != end; insn = NEXT_INSN (insn))
	if (memory_modified_in_insn_p (x, insn))
	  return 1;
      return 0;
      break;

    case REG:
      return reg_set_between_p (x, start, end);

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e' && modified_between_p (XEXP (x, i), start, end))
	return 1;

      else if (fmt[i] == 'E')
	for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	  if (modified_between_p (XVECEXP (x, i, j), start, end))
	    return 1;
    }

  return 0;
}