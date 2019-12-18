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
struct objfile {int dummy; } ;
struct dieinfo {int die_length; int /*<<< orphan*/  at_high_pc; int /*<<< orphan*/  at_low_pc; } ;
struct context_stack {int /*<<< orphan*/ * locals; int /*<<< orphan*/  start_addr; int /*<<< orphan*/  old_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  finish_block (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct objfile*) ; 
 int /*<<< orphan*/ * local_symbols ; 
 struct context_stack* pop_context () ; 
 int /*<<< orphan*/  process_dies (char*,char*,struct objfile*) ; 
 int /*<<< orphan*/  push_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_lexical_block_scope (struct dieinfo *dip, char *thisdie, char *enddie,
			  struct objfile *objfile)
{
  struct context_stack *new;

  push_context (0, dip->at_low_pc);
  process_dies (thisdie + dip->die_length, enddie, objfile);
  new = pop_context ();
  if (local_symbols != NULL)
    {
      finish_block (0, &local_symbols, new->old_blocks, new->start_addr,
		    dip->at_high_pc, objfile);
    }
  local_symbols = new->locals;
}