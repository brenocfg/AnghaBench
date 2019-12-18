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
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 scalar_t__ trunc_int_for_mode (scalar_t__,int) ; 

int
const_int_operand (rtx op, enum machine_mode mode)
{
  if (GET_CODE (op) != CONST_INT)
    return 0;

  if (mode != VOIDmode
      && trunc_int_for_mode (INTVAL (op), mode) != INTVAL (op))
    return 0;

  return 1;
}