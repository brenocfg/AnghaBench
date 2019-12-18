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
#define  CONST 137 
 int /*<<< orphan*/  CONSTANT_POOL_ADDRESS_P (int /*<<< orphan*/ ) ; 
#define  CONST_DOUBLE 136 
#define  CONST_INT 135 
#define  CONST_VECTOR 134 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  IF_THEN_ELSE 133 
#define  LABEL_REF 132 
#define  MEM 131 
#define  PC 130 
#define  REG 129 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
computed_jump_p_1 (rtx x)
{
  enum rtx_code code = GET_CODE (x);
  int i, j;
  const char *fmt;

  switch (code)
    {
    case LABEL_REF:
    case PC:
      return 0;

    case CONST:
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case SYMBOL_REF:
    case REG:
      return 1;

    case MEM:
      return ! (GET_CODE (XEXP (x, 0)) == SYMBOL_REF
		&& CONSTANT_POOL_ADDRESS_P (XEXP (x, 0)));

    case IF_THEN_ELSE:
      return (computed_jump_p_1 (XEXP (x, 1))
	      || computed_jump_p_1 (XEXP (x, 2)));

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e'
	  && computed_jump_p_1 (XEXP (x, i)))
	return 1;

      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  if (computed_jump_p_1 (XVECEXP (x, i, j)))
	    return 1;
    }

  return 0;
}