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
 scalar_t__ JUMP_P (scalar_t__) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NOTE_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 

__attribute__((used)) static rtx
first_active_insn (basic_block bb)
{
  rtx insn = BB_HEAD (bb);

  if (LABEL_P (insn))
    {
      if (insn == BB_END (bb))
	return NULL_RTX;
      insn = NEXT_INSN (insn);
    }

  while (NOTE_P (insn))
    {
      if (insn == BB_END (bb))
	return NULL_RTX;
      insn = NEXT_INSN (insn);
    }

  if (JUMP_P (insn))
    return NULL_RTX;

  return insn;
}