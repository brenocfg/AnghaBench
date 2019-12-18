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
 scalar_t__ CLOBBER ; 
 scalar_t__ CODE_FOR_stack_tie ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_CODE (scalar_t__) ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ USE ; 

__attribute__((used)) static rtx
get_next_active_insn (rtx insn, rtx tail)
{
  if (insn == NULL_RTX || insn == tail)
    return NULL_RTX;

  while (1)
    {
      insn = NEXT_INSN (insn);
      if (insn == NULL_RTX || insn == tail)
	return NULL_RTX;

      if (CALL_P (insn)
	  || JUMP_P (insn)
	  || (NONJUMP_INSN_P (insn)
	      && GET_CODE (PATTERN (insn)) != USE
	      && GET_CODE (PATTERN (insn)) != CLOBBER
	      && INSN_CODE (insn) != CODE_FOR_stack_tie))
	break;
    }
  return insn;
}