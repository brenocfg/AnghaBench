#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ entry_point; scalar_t__ entry_func_lowpc; scalar_t__ entry_func_highpc; } ;
struct objfile {TYPE_1__ ei; } ;
struct dieinfo {scalar_t__ at_low_pc; scalar_t__ at_high_pc; int die_length; int /*<<< orphan*/ * at_name; } ;
struct context_stack {int /*<<< orphan*/  start_addr; int /*<<< orphan*/  old_blocks; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_symbols ; 
 int /*<<< orphan*/  finish_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct objfile*) ; 
 int /*<<< orphan*/ * list_in_scope ; 
 int /*<<< orphan*/  local_symbols ; 
 int /*<<< orphan*/  new_symbol (struct dieinfo*,struct objfile*) ; 
 struct context_stack* pop_context () ; 
 int /*<<< orphan*/  process_dies (char*,char*,struct objfile*) ; 
 struct context_stack* push_context (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static void
read_func_scope (struct dieinfo *dip, char *thisdie, char *enddie,
		 struct objfile *objfile)
{
  struct context_stack *new;

  /* AT_name is absent if the function is described with an
     AT_abstract_origin tag.
     Ignore the function description for now to avoid GDB core dumps.
     FIXME: Add code to handle AT_abstract_origin tags properly.  */
  if (dip->at_name == NULL)
    {
      complaint (&symfile_complaints, "DIE @ 0x%x, AT_name tag missing",
		 DIE_ID);
      return;
    }

  if (objfile->ei.entry_point >= dip->at_low_pc &&
      objfile->ei.entry_point < dip->at_high_pc)
    {
      objfile->ei.entry_func_lowpc = dip->at_low_pc;
      objfile->ei.entry_func_highpc = dip->at_high_pc;
    }
  new = push_context (0, dip->at_low_pc);
  new->name = new_symbol (dip, objfile);
  list_in_scope = &local_symbols;
  process_dies (thisdie + dip->die_length, enddie, objfile);
  new = pop_context ();
  /* Make a block for the local symbols within.  */
  finish_block (new->name, &local_symbols, new->old_blocks,
		new->start_addr, dip->at_high_pc, objfile);
  list_in_scope = &file_symbols;
}