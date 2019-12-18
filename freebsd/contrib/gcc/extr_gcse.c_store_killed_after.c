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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ BB_END (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ store_killed_in_insn (scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  store_ops_ok (scalar_t__,int*) ; 

__attribute__((used)) static bool
store_killed_after (rtx x, rtx x_regs, rtx insn, basic_block bb,
		    int *regs_set_after, rtx *fail_insn)
{
  rtx last = BB_END (bb), act;

  if (!store_ops_ok (x_regs, regs_set_after))
    {
      /* We do not know where it will happen.  */
      if (fail_insn)
	*fail_insn = NULL_RTX;
      return true;
    }

  /* Scan from the end, so that fail_insn is determined correctly.  */
  for (act = last; act != PREV_INSN (insn); act = PREV_INSN (act))
    if (store_killed_in_insn (x, x_regs, act, false))
      {
	if (fail_insn)
	  *fail_insn = act;
	return true;
      }

  return false;
}