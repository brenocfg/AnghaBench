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
 int /*<<< orphan*/  BARRIER_P (scalar_t__) ; 
 scalar_t__ BB_END (int /*<<< orphan*/ ) ; 
 scalar_t__ BB_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  set_block_for_insn (scalar_t__,int /*<<< orphan*/ ) ; 

void
update_bb_for_insn (basic_block bb)
{
  rtx insn;

  for (insn = BB_HEAD (bb); ; insn = NEXT_INSN (insn))
    {
      if (!BARRIER_P (insn))
	set_block_for_insn (insn, bb);
      if (insn == BB_END (bb))
	break;
    }
}