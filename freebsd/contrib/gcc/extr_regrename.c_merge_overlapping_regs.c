#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct du_chain {scalar_t__ insn; struct du_chain* next_use; } ;
typedef  scalar_t__ rtx ;
typedef  TYPE_3__* basic_block ;
struct TYPE_7__ {TYPE_1__* rtl; } ;
struct TYPE_8__ {TYPE_2__ il; } ;
struct TYPE_6__ {int /*<<< orphan*/  global_live_at_start; } ;
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 scalar_t__ BB_HEAD (TYPE_3__*) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  IOR_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  REG_DEAD ; 
 int /*<<< orphan*/  REG_NOTES (scalar_t__) ; 
 int /*<<< orphan*/  REG_SET_TO_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UNUSED ; 
 int /*<<< orphan*/  clear_dead_regs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note_sets ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
merge_overlapping_regs (basic_block b, HARD_REG_SET *pset,
			struct du_chain *chain)
{
  struct du_chain *t = chain;
  rtx insn;
  HARD_REG_SET live;

  REG_SET_TO_HARD_REG_SET (live, b->il.rtl->global_live_at_start);
  insn = BB_HEAD (b);
  while (t)
    {
      /* Search forward until the next reference to the register to be
	 renamed.  */
      while (insn != t->insn)
	{
	  if (INSN_P (insn))
	    {
	      clear_dead_regs (&live, REG_DEAD, REG_NOTES (insn));
	      note_stores (PATTERN (insn), note_sets, (void *) &live);
	      /* Only record currently live regs if we are inside the
		 reg's live range.  */
	      if (t != chain)
		IOR_HARD_REG_SET (*pset, live);
	      clear_dead_regs (&live, REG_UNUSED, REG_NOTES (insn));
	    }
	  insn = NEXT_INSN (insn);
	}

      IOR_HARD_REG_SET (*pset, live);

      /* For the last reference, also merge in all registers set in the
	 same insn.
	 @@@ We only have take earlyclobbered sets into account.  */
      if (! t->next_use)
	note_stores (PATTERN (insn), note_sets, (void *) pset);

      t = t->next_use;
    }
}