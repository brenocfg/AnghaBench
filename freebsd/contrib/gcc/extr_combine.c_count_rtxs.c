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
 int GET_CODE (scalar_t__) ; 
 char GET_RTX_CLASS (int) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 

__attribute__((used)) static int
count_rtxs (rtx x)
{
  enum rtx_code code = GET_CODE (x);
  const char *fmt;
  int i, ret = 1;

  if (GET_RTX_CLASS (code) == '2'
      || GET_RTX_CLASS (code) == 'c')
    {
      rtx x0 = XEXP (x, 0);
      rtx x1 = XEXP (x, 1);

      if (x0 == x1)
	return 1 + 2 * count_rtxs (x0);

      if ((GET_RTX_CLASS (GET_CODE (x1)) == '2'
	   || GET_RTX_CLASS (GET_CODE (x1)) == 'c')
	  && (x0 == XEXP (x1, 0) || x0 == XEXP (x1, 1)))
	return 2 + 2 * count_rtxs (x0)
	       + count_rtxs (x == XEXP (x1, 0)
			     ? XEXP (x1, 1) : XEXP (x1, 0));

      if ((GET_RTX_CLASS (GET_CODE (x0)) == '2'
	   || GET_RTX_CLASS (GET_CODE (x0)) == 'c')
	  && (x1 == XEXP (x0, 0) || x1 == XEXP (x0, 1)))
	return 2 + 2 * count_rtxs (x1)
	       + count_rtxs (x == XEXP (x0, 0)
			     ? XEXP (x0, 1) : XEXP (x0, 0));
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    if (fmt[i] == 'e')
      ret += count_rtxs (XEXP (x, i));

  return ret;
}