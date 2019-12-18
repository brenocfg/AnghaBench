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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int MEM ; 
 scalar_t__ PC ; 
 int SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ refers_to_regno_p (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
reg_used_in_mem_p (int regno, rtx x)
{
  enum rtx_code code = GET_CODE (x);
  int i, j;
  const char *fmt;

  if (code == MEM)
    {
      if (refers_to_regno_p (regno, regno+1,
			     XEXP (x, 0), 0))
	return true;
    }
  else if (code == SET
	   && GET_CODE (SET_DEST (x)) == PC)
    {
      if (refers_to_regno_p (regno, regno+1,
			     SET_SRC (x), 0))
	return true;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e'
	  && reg_used_in_mem_p (regno, XEXP (x, i)))
	return true;

      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  if (reg_used_in_mem_p (regno, XVECEXP (x, i, j)))
	    return true;
    }
  return false;
}