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
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  SET_DEST (scalar_t__) ; 
 scalar_t__ STACK_REG_P (int /*<<< orphan*/ ) ; 
 int insn_rtx_cost (int /*<<< orphan*/ ) ; 
 scalar_t__ single_set (scalar_t__) ; 

__attribute__((used)) static bool
cheap_bb_rtx_cost_p (basic_block bb, int max_cost)
{
  int count = 0;
  rtx insn = BB_HEAD (bb);

  while (1)
    {
      if (NONJUMP_INSN_P (insn))
	{
	  int cost = insn_rtx_cost (PATTERN (insn));
	  if (cost == 0)
	    return false;

	  /* If this instruction is the load or set of a "stack" register,
	     such as a floating point register on x87, then the cost of
	     speculatively executing this insn may need to include
	     the additional cost of popping its result off of the
	     register stack.  Unfortunately, correctly recognizing and
	     accounting for this additional overhead is tricky, so for
	     now we simply prohibit such speculative execution.  */
#ifdef STACK_REGS
	  {
	    rtx set = single_set (insn);
	    if (set && STACK_REG_P (SET_DEST (set)))
	      return false;
	  }
#endif

	  count += cost;
	  if (count >= max_cost)
	    return false;
	}
      else if (CALL_P (insn))
	return false;
 
      if (insn == BB_END (bb))
	break;
      insn = NEXT_INSN (insn);
    }

  return true;
}