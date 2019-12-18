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
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 int /*<<< orphan*/  SET_INSN_DELETED (scalar_t__) ; 
 int /*<<< orphan*/  cleanup_subreg_operands (scalar_t__) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ try_split (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static rtx
split_insn (rtx insn)
{
  /* Split insns here to get max fine-grain parallelism.  */
  rtx first = PREV_INSN (insn);
  rtx last = try_split (PATTERN (insn), insn, 1);

  if (last == insn)
    return NULL_RTX;

  /* try_split returns the NOTE that INSN became.  */
  SET_INSN_DELETED (insn);

  /* ??? Coddle to md files that generate subregs in post-reload
     splitters instead of computing the proper hard register.  */
  if (reload_completed && first != last)
    {
      first = NEXT_INSN (first);
      for (;;)
	{
	  if (INSN_P (first))
	    cleanup_subreg_operands (first);
	  if (first == last)
	    break;
	  first = NEXT_INSN (first);
	}
    }
  return last;
}