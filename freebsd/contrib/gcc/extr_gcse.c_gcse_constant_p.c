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
 scalar_t__ COMPARE ; 
 int CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
gcse_constant_p (rtx x)
{
  /* Consider a COMPARE of two integers constant.  */
  if (GET_CODE (x) == COMPARE
      && GET_CODE (XEXP (x, 0)) == CONST_INT
      && GET_CODE (XEXP (x, 1)) == CONST_INT)
    return true;

  /* Consider a COMPARE of the same registers is a constant
     if they are not floating point registers.  */
  if (GET_CODE(x) == COMPARE
      && REG_P (XEXP (x, 0)) && REG_P (XEXP (x, 1))
      && REGNO (XEXP (x, 0)) == REGNO (XEXP (x, 1))
      && ! FLOAT_MODE_P (GET_MODE (XEXP (x, 0)))
      && ! FLOAT_MODE_P (GET_MODE (XEXP (x, 1))))
    return true;

  return CONSTANT_P (x);
}