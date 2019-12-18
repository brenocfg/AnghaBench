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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  fold_rtx_mem_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int table_size ; 

__attribute__((used)) static rtx
fold_rtx_mem (rtx x, rtx insn)
{
  /* To avoid infinite oscillations between fold_rtx and fold_rtx_mem,
     refuse to allow recursion of the latter past n levels.  This can
     happen because fold_rtx_mem will try to fold the address of the
     memory reference it is passed, i.e. conceptually throwing away
     the MEM and reinjecting the bare address into fold_rtx.  As a
     result, patterns like

       set (reg1)
	   (plus (reg)
		 (mem (plus (reg2) (const_int))))

       set (reg2)
	   (plus (reg)
		 (mem (plus (reg1) (const_int))))

     will defeat any "first-order" short-circuit put in either
     function to prevent these infinite oscillations.

     The heuristics for determining n is as follows: since each time
     it is invoked fold_rtx_mem throws away a MEM, and since MEMs
     are generically not nested, we assume that each invocation of
     fold_rtx_mem corresponds to a new "top-level" operand, i.e.
     the source or the destination of a SET.  So fold_rtx_mem is
     bound to stop or cycle before n recursions, n being the number
     of expressions recorded in the hash table.  We also leave some
     play to account for the initial steps.  */

  static unsigned int depth;
  rtx ret;

  if (depth > 3 + table_size)
    return x;

  depth++;
  ret = fold_rtx_mem_1 (x, insn);
  depth--;

  return ret;
}