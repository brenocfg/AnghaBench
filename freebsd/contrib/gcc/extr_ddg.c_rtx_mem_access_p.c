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
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 

__attribute__((used)) static bool
rtx_mem_access_p (rtx x)
{
  int i, j;
  const char *fmt;
  enum rtx_code code;

  if (x == 0)
    return false;

  if (MEM_P (x))
    return true;

  code = GET_CODE (x);
  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  if (rtx_mem_access_p (XEXP (x, i)))
            return true;
        }
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  {
	    if (rtx_mem_access_p (XVECEXP (x, i, j)))
              return true;
          }
    }
  return false;
}