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
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  MINUS 129 
#define  PLUS 128 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
simple_rhs_p (rtx rhs)
{
  rtx op0, op1;

  if (CONSTANT_P (rhs)
      || REG_P (rhs))
    return true;

  switch (GET_CODE (rhs))
    {
    case PLUS:
    case MINUS:
      op0 = XEXP (rhs, 0);
      op1 = XEXP (rhs, 1);
      /* Allow reg + const sets only.  */
      if (REG_P (op0) && CONSTANT_P (op1))
	return true;
      if (REG_P (op1) && CONSTANT_P (op0))
	return true;

      return false;

    default:
      return false;
    }
}