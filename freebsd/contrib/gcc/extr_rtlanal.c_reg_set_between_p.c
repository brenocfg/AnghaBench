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
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ reg_set_p (scalar_t__,scalar_t__) ; 

int
reg_set_between_p (rtx reg, rtx from_insn, rtx to_insn)
{
  rtx insn;

  if (from_insn == to_insn)
    return 0;

  for (insn = NEXT_INSN (from_insn); insn != to_insn; insn = NEXT_INSN (insn))
    if (INSN_P (insn) && reg_set_p (reg, insn))
      return 1;
  return 0;
}