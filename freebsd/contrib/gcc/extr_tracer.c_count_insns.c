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
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ active_insn_p (scalar_t__) ; 

__attribute__((used)) static int
count_insns (basic_block bb)
{
  rtx insn;
  int n = 0;

  for (insn = BB_HEAD (bb);
       insn != NEXT_INSN (BB_END (bb));
       insn = NEXT_INSN (insn))
    if (active_insn_p (insn))
      n++;
  return n;
}