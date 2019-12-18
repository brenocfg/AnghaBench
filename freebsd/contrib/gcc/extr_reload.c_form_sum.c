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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST ; 
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS ; 
 int Pmode ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_CONST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
form_sum (rtx x, rtx y)
{
  rtx tem;
  enum machine_mode mode = GET_MODE (x);

  if (mode == VOIDmode)
    mode = GET_MODE (y);

  if (mode == VOIDmode)
    mode = Pmode;

  if (GET_CODE (x) == CONST_INT)
    return plus_constant (y, INTVAL (x));
  else if (GET_CODE (y) == CONST_INT)
    return plus_constant (x, INTVAL (y));
  else if (CONSTANT_P (x))
    tem = x, x = y, y = tem;

  if (GET_CODE (x) == PLUS && CONSTANT_P (XEXP (x, 1)))
    return form_sum (XEXP (x, 0), form_sum (XEXP (x, 1), y));

  /* Note that if the operands of Y are specified in the opposite
     order in the recursive calls below, infinite recursion will occur.  */
  if (GET_CODE (y) == PLUS && CONSTANT_P (XEXP (y, 1)))
    return form_sum (form_sum (x, XEXP (y, 0)), XEXP (y, 1));

  /* If both constant, encapsulate sum.  Otherwise, just form sum.  A
     constant will have been placed second.  */
  if (CONSTANT_P (x) && CONSTANT_P (y))
    {
      if (GET_CODE (x) == CONST)
	x = XEXP (x, 0);
      if (GET_CODE (y) == CONST)
	y = XEXP (y, 0);

      return gen_rtx_CONST (VOIDmode, gen_rtx_PLUS (mode, x, y));
    }

  return gen_rtx_PLUS (mode, x, y);
}