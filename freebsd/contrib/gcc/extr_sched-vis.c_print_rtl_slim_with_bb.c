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
typedef  int /*<<< orphan*/ * rtx ;
typedef  int /*<<< orphan*/ * basic_block ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * BB_END (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BLOCK_FOR_INSN (int /*<<< orphan*/ *) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ INSN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NEXT_INSN (int /*<<< orphan*/ *) ; 
 scalar_t__ NOTE ; 
 int TDF_BLOCKS ; 
 int /*<<< orphan*/  dump_bb_info (int /*<<< orphan*/ *,int,int,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_insn_slim (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
print_rtl_slim_with_bb (FILE *f, rtx first, int flags)
{
  basic_block current_bb = NULL;
  rtx insn;

  for (insn = first; NULL != insn; insn = NEXT_INSN (insn))
    {
      if ((flags & TDF_BLOCKS)
	  && (INSN_P (insn) || GET_CODE (insn) == NOTE)
	  && BLOCK_FOR_INSN (insn)
	  && !current_bb)
	{
	  current_bb = BLOCK_FOR_INSN (insn);
	  dump_bb_info (current_bb, true, false, flags, ";; ", f);
	}

      dump_insn_slim (f, insn);

      if ((flags & TDF_BLOCKS)
	  && current_bb
	  && insn == BB_END (current_bb))
	{
	  dump_bb_info (current_bb, false, true, flags, ";; ", f);
	  current_bb = NULL;
	}
    }
}