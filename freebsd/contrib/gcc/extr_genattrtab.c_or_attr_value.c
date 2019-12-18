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
#define  COND 130 
#define  CONST_STRING 129 
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  IF_THEN_ELSE 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atoi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
or_attr_value (rtx exp, int *unknownp)
{
  int current_or;
  int i;

  switch (GET_CODE (exp))
    {
    case CONST_STRING:
      current_or = atoi (XSTR (exp, 0));
      break;

    case COND:
      current_or = or_attr_value (XEXP (exp, 1), unknownp);
      for (i = 0; i < XVECLEN (exp, 0); i += 2)
	current_or |= or_attr_value (XVECEXP (exp, 0, i + 1), unknownp);
      break;

    case IF_THEN_ELSE:
      current_or = or_attr_value (XEXP (exp, 1), unknownp);
      current_or |= or_attr_value (XEXP (exp, 2), unknownp);
      break;

    default:
      *unknownp = 1;
      current_or = -1;
      break;
    }

  return current_or;
}