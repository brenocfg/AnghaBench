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

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (scalar_t__) ; 
 int GET_RTX_LENGTH (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ UNSPEC ; 
 scalar_t__ UNSPEC_LTREL_BASE ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XINT (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 

__attribute__((used)) static rtx
find_ltrel_base (rtx x)
{
  int i, j;
  const char *fmt;

  if (GET_CODE (x) == UNSPEC
      && XINT (x, 1) == UNSPEC_LTREL_BASE)
    return XVECEXP (x, 0, 0);

  fmt = GET_RTX_FORMAT (GET_CODE (x));
  for (i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
        {
          rtx fnd = find_ltrel_base (XEXP (x, i));
	  if (fnd)
	    return fnd;
        }
      else if (fmt[i] == 'E')
        {
          for (j = 0; j < XVECLEN (x, i); j++)
	    {
              rtx fnd = find_ltrel_base (XVECEXP (x, i, j));
	      if (fnd)
		return fnd;
	    }
        }
    }

  return NULL_RTX;
}