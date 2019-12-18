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
 int LABEL_REF ; 
 scalar_t__ OBJECT_P (scalar_t__) ; 
 int SYMBOL_REF ; 
 scalar_t__ XEXP (scalar_t__,int) ; 

__attribute__((used)) static rtx
find_symbolic_term (rtx x)
{
  int i;
  enum rtx_code code;
  const char *fmt;

  code = GET_CODE (x);
  if (code == SYMBOL_REF || code == LABEL_REF)
    return x;
  if (OBJECT_P (x))
    return 0;

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      rtx t;

      if (fmt[i] == 'e')
	{
	  t = find_symbolic_term (XEXP (x, i));
	  if (t != 0)
	    return t;
	}
      else if (fmt[i] == 'E')
	break;
    }
  return 0;
}