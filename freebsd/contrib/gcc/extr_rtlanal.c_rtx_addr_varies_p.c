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
 scalar_t__ BLKmode ; 
 int GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int MEM ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 scalar_t__ rtx_varies_p (scalar_t__,int) ; 

int
rtx_addr_varies_p (rtx x, int for_alias)
{
  enum rtx_code code;
  int i;
  const char *fmt;

  if (x == 0)
    return 0;

  code = GET_CODE (x);
  if (code == MEM)
    return GET_MODE (x) == BLKmode || rtx_varies_p (XEXP (x, 0), for_alias);

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    if (fmt[i] == 'e')
      {
	if (rtx_addr_varies_p (XEXP (x, i), for_alias))
	  return 1;
      }
    else if (fmt[i] == 'E')
      {
	int j;
	for (j = 0; j < XVECLEN (x, i); j++)
	  if (rtx_addr_varies_p (XVECEXP (x, i, j), for_alias))
	    return 1;
      }
  return 0;
}