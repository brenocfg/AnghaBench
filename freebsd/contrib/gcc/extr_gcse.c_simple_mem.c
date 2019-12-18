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
 scalar_t__ BLKmode ; 
 scalar_t__ FLOAT_MODE_P (scalar_t__) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_float_store ; 
 scalar_t__ flag_non_call_exceptions ; 
 scalar_t__ may_trap_p (int /*<<< orphan*/ ) ; 
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ side_effects_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

__attribute__((used)) static int
simple_mem (rtx x)
{
  if (! MEM_P (x))
    return 0;

  if (MEM_VOLATILE_P (x))
    return 0;

  if (GET_MODE (x) == BLKmode)
    return 0;

  /* If we are handling exceptions, we must be careful with memory references
     that may trap. If we are not, the behavior is undefined, so we may just
     continue.  */
  if (flag_non_call_exceptions && may_trap_p (x))
    return 0;

  if (side_effects_p (x))
    return 0;

  /* Do not consider function arguments passed on stack.  */
  if (reg_mentioned_p (stack_pointer_rtx, x))
    return 0;

  if (flag_float_store && FLOAT_MODE_P (GET_MODE (x)))
    return 0;

  return 1;
}