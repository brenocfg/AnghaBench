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
struct symtab_and_line {scalar_t__ pc; scalar_t__ end; } ;
struct symbol {int dummy; } ;
struct linked_proc_info {int /*<<< orphan*/  info; struct linked_proc_info* next; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/ * mips_extra_func_info_t ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_START (int /*<<< orphan*/ ) ; 
 scalar_t__ PROC_DESC_IS_DUMMY (int /*<<< orphan*/ *) ; 
 scalar_t__ PROC_HIGH_ADDR (int /*<<< orphan*/ *) ; 
 scalar_t__ PROC_LOW_ADDR (int /*<<< orphan*/ *) ; 
 struct symbol* PROC_SYMBOL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 struct symtab_and_line find_pc_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heuristic_proc_desc (scalar_t__,scalar_t__,struct frame_info*,int) ; 
 scalar_t__ heuristic_proc_start (scalar_t__) ; 
 struct linked_proc_info* linked_proc_desc_table ; 
 int /*<<< orphan*/ * non_heuristic_proc_desc (scalar_t__,scalar_t__*) ; 

__attribute__((used)) static mips_extra_func_info_t
find_proc_desc (CORE_ADDR pc, struct frame_info *next_frame, int cur_frame)
{
  mips_extra_func_info_t proc_desc;
  CORE_ADDR startaddr = 0;

  proc_desc = non_heuristic_proc_desc (pc, &startaddr);

  if (proc_desc)
    {
      /* IF this is the topmost frame AND
       * (this proc does not have debugging information OR
       * the PC is in the procedure prologue)
       * THEN create a "heuristic" proc_desc (by analyzing
       * the actual code) to replace the "official" proc_desc.
       */
      if (next_frame == NULL)
	{
	  struct symtab_and_line val;
	  struct symbol *proc_symbol =
	    PROC_DESC_IS_DUMMY (proc_desc) ? 0 : PROC_SYMBOL (proc_desc);

	  if (proc_symbol)
	    {
	      val = find_pc_line (BLOCK_START
				  (SYMBOL_BLOCK_VALUE (proc_symbol)), 0);
	      val.pc = val.end ? val.end : pc;
	    }
	  if (!proc_symbol || pc < val.pc)
	    {
	      mips_extra_func_info_t found_heuristic =
		heuristic_proc_desc (PROC_LOW_ADDR (proc_desc),
				     pc, next_frame, cur_frame);
	      if (found_heuristic)
		proc_desc = found_heuristic;
	    }
	}
    }
  else
    {
      /* Is linked_proc_desc_table really necessary?  It only seems to be used
         by procedure call dummys.  However, the procedures being called ought
         to have their own proc_descs, and even if they don't,
         heuristic_proc_desc knows how to create them! */

      struct linked_proc_info *link;

      for (link = linked_proc_desc_table; link; link = link->next)
	if (PROC_LOW_ADDR (&link->info) <= pc
	    && PROC_HIGH_ADDR (&link->info) > pc)
	  return &link->info;

      if (startaddr == 0)
	startaddr = heuristic_proc_start (pc);

      proc_desc = heuristic_proc_desc (startaddr, pc, next_frame, cur_frame);
    }
  return proc_desc;
}