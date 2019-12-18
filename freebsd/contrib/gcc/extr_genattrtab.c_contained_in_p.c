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

/* Variables and functions */
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int /*<<< orphan*/ ) ; 
 int GET_RTX_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
contained_in_p (rtx inner, rtx exp)
{
  int i, j;
  const char *fmt;

  if (rtx_equal_p (inner, exp))
    return 1;

  for (i = 0, fmt = GET_RTX_FORMAT (GET_CODE (exp));
       i < GET_RTX_LENGTH (GET_CODE (exp)); i++)
    switch (*fmt++)
      {
      case 'e':
      case 'u':
	if (contained_in_p (inner, XEXP (exp, i)))
	  return 1;
	break;

      case 'E':
	for (j = 0; j < XVECLEN (exp, i); j++)
	  if (contained_in_p (inner, XVECEXP (exp, i, j)))
	    return 1;
	break;
      }

  return 0;
}