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

/* Variables and functions */
 scalar_t__ CALL_P (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  USE ; 
 scalar_t__ find_reg_fusage (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ reg_overlap_mentioned_p (scalar_t__,int /*<<< orphan*/ ) ; 

int
reg_used_between_p (rtx reg, rtx from_insn, rtx to_insn)
{
  rtx insn;

  if (from_insn == to_insn)
    return 0;

  for (insn = NEXT_INSN (from_insn); insn != to_insn; insn = NEXT_INSN (insn))
    if (INSN_P (insn)
	&& (reg_overlap_mentioned_p (reg, PATTERN (insn))
	   || (CALL_P (insn) && find_reg_fusage (insn, USE, reg))))
      return 1;
  return 0;
}