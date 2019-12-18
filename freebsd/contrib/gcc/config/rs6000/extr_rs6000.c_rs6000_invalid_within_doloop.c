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
 scalar_t__ ADDR_DIFF_VEC ; 
 scalar_t__ ADDR_VEC ; 
 scalar_t__ CALL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ JUMP_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
rs6000_invalid_within_doloop (rtx insn)
{
  if (CALL_P (insn))
    return "Function call in the loop.";

  if (JUMP_P (insn)
      && (GET_CODE (PATTERN (insn)) == ADDR_DIFF_VEC
	  || GET_CODE (PATTERN (insn)) == ADDR_VEC))
    return "Computed branch in the loop.";

  return NULL;
}