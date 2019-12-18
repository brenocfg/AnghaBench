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
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int INTVAL (scalar_t__) ; 
 int MEM ; 
 scalar_t__ PLUS ; 
 scalar_t__ POST_DEC ; 
 scalar_t__ POST_INC ; 
 scalar_t__ POST_MODIFY ; 
 scalar_t__ PRE_DEC ; 
 scalar_t__ PRE_INC ; 
 scalar_t__ PRE_MODIFY ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 

__attribute__((used)) static int
find_inc_amount (rtx x, rtx inced)
{
  enum rtx_code code = GET_CODE (x);
  const char *fmt;
  int i;

  if (code == MEM)
    {
      rtx addr = XEXP (x, 0);
      if ((GET_CODE (addr) == PRE_DEC
	   || GET_CODE (addr) == POST_DEC
	   || GET_CODE (addr) == PRE_INC
	   || GET_CODE (addr) == POST_INC)
	  && XEXP (addr, 0) == inced)
	return GET_MODE_SIZE (GET_MODE (x));
      else if ((GET_CODE (addr) == PRE_MODIFY
		|| GET_CODE (addr) == POST_MODIFY)
	       && GET_CODE (XEXP (addr, 1)) == PLUS
	       && XEXP (addr, 0) == XEXP (XEXP (addr, 1), 0)
	       && XEXP (addr, 0) == inced
	       && GET_CODE (XEXP (XEXP (addr, 1), 1)) == CONST_INT)
	{
	  i = INTVAL (XEXP (XEXP (addr, 1), 1));
	  return i < 0 ? -i : i;
	}
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  int tem = find_inc_amount (XEXP (x, i), inced);
	  if (tem != 0)
	    return tem;
	}
      if (fmt[i] == 'E')
	{
	  int j;
	  for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	    {
	      int tem = find_inc_amount (XVECEXP (x, i, j), inced);
	      if (tem != 0)
		return tem;
	    }
	}
    }

  return 0;
}