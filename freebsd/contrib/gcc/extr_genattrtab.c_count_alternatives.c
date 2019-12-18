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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (scalar_t__) ; 
 int GET_RTX_LENGTH (scalar_t__) ; 
 scalar_t__ MATCH_OPERAND ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * XVEC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int n_comma_elts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
count_alternatives (rtx exp)
{
  int i, j, n;
  const char *fmt;

  if (GET_CODE (exp) == MATCH_OPERAND)
    return n_comma_elts (XSTR (exp, 2));

  for (i = 0, fmt = GET_RTX_FORMAT (GET_CODE (exp));
       i < GET_RTX_LENGTH (GET_CODE (exp)); i++)
    switch (*fmt++)
      {
      case 'e':
      case 'u':
	n = count_alternatives (XEXP (exp, i));
	if (n)
	  return n;
	break;

      case 'E':
      case 'V':
	if (XVEC (exp, i) != NULL)
	  for (j = 0; j < XVECLEN (exp, i); j++)
	    {
	      n = count_alternatives (XVECEXP (exp, i, j));
	      if (n)
		return n;
	    }
      }

  return 0;
}