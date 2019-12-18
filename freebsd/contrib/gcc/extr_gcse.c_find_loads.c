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
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ SET ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 scalar_t__ load_kills_store (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static bool
find_loads (rtx x, rtx store_pattern, int after)
{
  const char * fmt;
  int i, j;
  int ret = false;

  if (!x)
    return false;

  if (GET_CODE (x) == SET)
    x = SET_SRC (x);

  if (MEM_P (x))
    {
      if (load_kills_store (x, store_pattern, after))
	return true;
    }

  /* Recursively process the insn.  */
  fmt = GET_RTX_FORMAT (GET_CODE (x));

  for (i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0 && !ret; i--)
    {
      if (fmt[i] == 'e')
	ret |= find_loads (XEXP (x, i), store_pattern, after);
      else if (fmt[i] == 'E')
	for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	  ret |= find_loads (XVECEXP (x, i, j), store_pattern, after);
    }
  return ret;
}