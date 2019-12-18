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
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_FUNCTION_VALUE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ active_insn_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
flow_active_insn_p (rtx insn)
{
  if (active_insn_p (insn))
    return true;

  /* A clobber of the function return value exists for buggy
     programs that fail to return a value.  Its effect is to
     keep the return value from being live across the entire
     function.  If we allow it to be skipped, we introduce the
     possibility for register lifetime confusion.  */
  if (GET_CODE (PATTERN (insn)) == CLOBBER
      && REG_P (XEXP (PATTERN (insn), 0))
      && REG_FUNCTION_VALUE_P (XEXP (PATTERN (insn), 0)))
    return true;

  return false;
}