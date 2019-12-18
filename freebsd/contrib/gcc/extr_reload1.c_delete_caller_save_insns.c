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
struct insn_chain {struct insn_chain* next; TYPE_1__* prev; int /*<<< orphan*/  insn; scalar_t__ is_caller_save_insn; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {struct insn_chain* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_insn (int /*<<< orphan*/ ) ; 
 struct insn_chain* reload_insn_chain ; 
 struct insn_chain* unused_insn_chains ; 

__attribute__((used)) static void
delete_caller_save_insns (void)
{
  struct insn_chain *c = reload_insn_chain;

  while (c != 0)
    {
      while (c != 0 && c->is_caller_save_insn)
	{
	  struct insn_chain *next = c->next;
	  rtx insn = c->insn;

	  if (c == reload_insn_chain)
	    reload_insn_chain = next;
	  delete_insn (insn);

	  if (next)
	    next->prev = c->prev;
	  if (c->prev)
	    c->prev->next = next;
	  c->next = unused_insn_chains;
	  unused_insn_chains = c;
	  c = next;
	}
      if (c != 0)
	c = c->next;
    }
}