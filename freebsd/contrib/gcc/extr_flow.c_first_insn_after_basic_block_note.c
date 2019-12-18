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
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  NOTE_INSN_BASIC_BLOCK_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

rtx
first_insn_after_basic_block_note (basic_block block)
{
  rtx insn;

  /* Get the first instruction in the block.  */
  insn = BB_HEAD (block);

  if (insn == NULL_RTX)
    return NULL_RTX;
  if (LABEL_P (insn))
    insn = NEXT_INSN (insn);
  gcc_assert (NOTE_INSN_BASIC_BLOCK_P (insn));

  return NEXT_INSN (insn);
}