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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 
 scalar_t__ NOTE_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ USE ; 

__attribute__((used)) static rtx
last_active_insn (basic_block bb, int skip_use_p)
{
  rtx insn = BB_END (bb);
  rtx head = BB_HEAD (bb);

  while (NOTE_P (insn)
	 || JUMP_P (insn)
	 || (skip_use_p
	     && NONJUMP_INSN_P (insn)
	     && GET_CODE (PATTERN (insn)) == USE))
    {
      if (insn == head)
	return NULL_RTX;
      insn = PREV_INSN (insn);
    }

  if (LABEL_P (insn))
    return NULL_RTX;

  return insn;
}