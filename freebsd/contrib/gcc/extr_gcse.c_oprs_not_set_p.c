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
#define  ADDR_DIFF_VEC 139 
#define  ADDR_VEC 138 
 int /*<<< orphan*/  BLOCK_FOR_INSN (scalar_t__) ; 
#define  CC0 137 
#define  CONST 136 
#define  CONST_DOUBLE 135 
#define  CONST_INT 134 
#define  CONST_VECTOR 133 
 int GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int /*<<< orphan*/  INSN_CUID (scalar_t__) ; 
#define  LABEL_REF 132 
#define  MEM 131 
#define  PC 130 
#define  REG 129 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REGNO_REG_SET_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SYMBOL_REF 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  load_killed_in_block_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_set_bitmap ; 

__attribute__((used)) static int
oprs_not_set_p (rtx x, rtx insn)
{
  int i, j;
  enum rtx_code code;
  const char *fmt;

  if (x == 0)
    return 1;

  code = GET_CODE (x);
  switch (code)
    {
    case PC:
    case CC0:
    case CONST:
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case SYMBOL_REF:
    case LABEL_REF:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
      return 1;

    case MEM:
      if (load_killed_in_block_p (BLOCK_FOR_INSN (insn),
				  INSN_CUID (insn), x, 0))
	return 0;
      else
	return oprs_not_set_p (XEXP (x, 0), insn);

    case REG:
      return ! REGNO_REG_SET_P (reg_set_bitmap, REGNO (x));

    default:
      break;
    }

  for (i = GET_RTX_LENGTH (code) - 1, fmt = GET_RTX_FORMAT (code); i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  /* If we are about to do the last recursive call
	     needed at this level, change it into iteration.
	     This function is called enough to be worth it.  */
	  if (i == 0)
	    return oprs_not_set_p (XEXP (x, i), insn);

	  if (! oprs_not_set_p (XEXP (x, i), insn))
	    return 0;
	}
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  if (! oprs_not_set_p (XVECEXP (x, i, j), insn))
	    return 0;
    }

  return 1;
}