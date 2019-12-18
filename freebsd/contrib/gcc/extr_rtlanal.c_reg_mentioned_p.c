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
#define  CC0 134 
#define  CONST_DOUBLE 133 
#define  CONST_INT 132 
#define  CONST_VECTOR 131 
 int GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int LABEL_REF ; 
#define  PC 130 
#define  REG 129 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
#define  SCRATCH 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

int
reg_mentioned_p (rtx reg, rtx in)
{
  const char *fmt;
  int i;
  enum rtx_code code;

  if (in == 0)
    return 0;

  if (reg == in)
    return 1;

  if (GET_CODE (in) == LABEL_REF)
    return reg == XEXP (in, 0);

  code = GET_CODE (in);

  switch (code)
    {
      /* Compare registers by number.  */
    case REG:
      return REG_P (reg) && REGNO (in) == REGNO (reg);

      /* These codes have no constituent expressions
	 and are unique.  */
    case SCRATCH:
    case CC0:
    case PC:
      return 0;

    case CONST_INT:
    case CONST_VECTOR:
    case CONST_DOUBLE:
      /* These are kept unique for a given value.  */
      return 0;

    default:
      break;
    }

  if (GET_CODE (reg) == code && rtx_equal_p (reg, in))
    return 1;

  fmt = GET_RTX_FORMAT (code);

  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'E')
	{
	  int j;
	  for (j = XVECLEN (in, i) - 1; j >= 0; j--)
	    if (reg_mentioned_p (reg, XVECEXP (in, i, j)))
	      return 1;
	}
      else if (fmt[i] == 'e'
	       && reg_mentioned_p (reg, XEXP (in, i)))
	return 1;
    }
  return 0;
}