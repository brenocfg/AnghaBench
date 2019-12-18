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
 scalar_t__ BB_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ CALL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 

__attribute__((used)) static int
count_bb_insns (basic_block bb)
{
  int count = 0;
  rtx insn = BB_HEAD (bb);

  while (1)
    {
      if (CALL_P (insn) || NONJUMP_INSN_P (insn))
	count++;

      if (insn == BB_END (bb))
	break;
      insn = NEXT_INSN (insn);
    }

  return count;
}