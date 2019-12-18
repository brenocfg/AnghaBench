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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE_SIZE (int) ; 
 int INTVAL (scalar_t__) ; 
 scalar_t__ TARGET_MIPS16 ; 
 scalar_t__ stack_pointer_rtx ; 

__attribute__((used)) static bool
mips16_unextended_reference_p (enum machine_mode mode, rtx base, rtx offset)
{
  if (TARGET_MIPS16
      && GET_CODE (offset) == CONST_INT
      && INTVAL (offset) >= 0
      && (INTVAL (offset) & (GET_MODE_SIZE (mode) - 1)) == 0)
    {
      if (GET_MODE_SIZE (mode) == 4 && base == stack_pointer_rtx)
	return INTVAL (offset) < 256 * GET_MODE_SIZE (mode);
      return INTVAL (offset) < 32 * GET_MODE_SIZE (mode);
    }
  return false;
}