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
typedef  int RTX_CODE ;

/* Variables and functions */
#define  ADDR_DIFF_VEC 151 
#define  ADDR_VEC 150 
#define  ASM_INPUT 149 
#define  ASM_OPERANDS 148 
#define  CALL 147 
#define  CC0 146 
#define  CLOBBER 145 
#define  CONST 144 
#define  CONST_DOUBLE 143 
#define  CONST_INT 142 
#define  CONST_VECTOR 141 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  LABEL_REF 140 
#define  MEM 139 
 int /*<<< orphan*/  MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
#define  PC 138 
#define  POST_DEC 137 
#define  POST_INC 136 
#define  POST_MODIFY 135 
#define  PRE_DEC 134 
#define  PRE_INC 133 
#define  PRE_MODIFY 132 
#define  REG 131 
#define  SCRATCH 130 
#define  SYMBOL_REF 129 
#define  UNSPEC_VOLATILE 128 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 

int
side_effects_p (rtx x)
{
  RTX_CODE code;

  code = GET_CODE (x);
  switch (code)
    {
    case LABEL_REF:
    case SYMBOL_REF:
    case CONST_INT:
    case CONST:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case CC0:
    case PC:
    case REG:
    case SCRATCH:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
      return 0;

    case CLOBBER:
      /* Reject CLOBBER with a non-VOID mode.  These are made by combine.c
	 when some combination can't be done.  If we see one, don't think
	 that we can simplify the expression.  */
      return (GET_MODE (x) != VOIDmode);

    case PRE_INC:
    case PRE_DEC:
    case POST_INC:
    case POST_DEC:
    case PRE_MODIFY:
    case POST_MODIFY:
    case CALL:
    case UNSPEC_VOLATILE:
 /* case TRAP_IF: This isn't clear yet.  */
      return 1;

    case MEM:
    case ASM_INPUT:
    case ASM_OPERANDS:
      if (MEM_VOLATILE_P (x))
	return 1;

    default:
      break;
    }

  /* Recursively scan the operands of this expression.  */

  {
    const char *fmt = GET_RTX_FORMAT (code);
    int i;

    for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
      {
	if (fmt[i] == 'e')
	  {
	    if (side_effects_p (XEXP (x, i)))
	      return 1;
	  }
	else if (fmt[i] == 'E')
	  {
	    int j;
	    for (j = 0; j < XVECLEN (x, i); j++)
	      if (side_effects_p (XVECEXP (x, i, j)))
		return 1;
	  }
      }
  }
  return 0;
}