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
 scalar_t__ BB_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ store_killed_in_insn (scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  store_ops_ok (scalar_t__,int*) ; 

__attribute__((used)) static bool
store_killed_before (rtx x, rtx x_regs, rtx insn, basic_block bb,
		     int *regs_set_before)
{
  rtx first = BB_HEAD (bb);

  if (!store_ops_ok (x_regs, regs_set_before))
    return true;

  for ( ; insn != PREV_INSN (first); insn = PREV_INSN (insn))
    if (store_killed_in_insn (x, x_regs, insn, true))
      return true;

  return false;
}