#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ noreorder; scalar_t__ mips16; } ;
struct TYPE_5__ {int fixed_p; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  NOP_INSN ; 
 int /*<<< orphan*/  add_fixed_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_grow (int) ; 
 int /*<<< orphan*/  frag_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_now ; 
 int /*<<< orphan*/  frag_wane (int /*<<< orphan*/ ) ; 
 TYPE_1__* history ; 
 int /*<<< orphan*/  mips16_mark_labels () ; 
 int mips_any_noreorder ; 
 int /*<<< orphan*/  mips_clear_insn_labels () ; 
 int /*<<< orphan*/  mips_move_labels () ; 
 scalar_t__ mips_optimize ; 
 TYPE_2__ mips_opts ; 
 int nops_for_insn (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prev_nop_frag ; 
 int prev_nop_frag_holds ; 
 scalar_t__ prev_nop_frag_required ; 
 scalar_t__ prev_nop_frag_since ; 

__attribute__((used)) static void
start_noreorder (void)
{
  if (mips_opts.noreorder == 0)
    {
      unsigned int i;
      int nops;

      /* None of the instructions before the .set noreorder can be moved.  */
      for (i = 0; i < ARRAY_SIZE (history); i++)
	history[i].fixed_p = 1;

      /* Insert any nops that might be needed between the .set noreorder
	 block and the previous instructions.  We will later remove any
	 nops that turn out not to be needed.  */
      nops = nops_for_insn (history, NULL);
      if (nops > 0)
	{
	  if (mips_optimize != 0)
	    {
	      /* Record the frag which holds the nop instructions, so
                 that we can remove them if we don't need them.  */
	      frag_grow (mips_opts.mips16 ? nops * 2 : nops * 4);
	      prev_nop_frag = frag_now;
	      prev_nop_frag_holds = nops;
	      prev_nop_frag_required = 0;
	      prev_nop_frag_since = 0;
	    }

	  for (; nops > 0; --nops)
	    add_fixed_insn (NOP_INSN);

	  /* Move on to a new frag, so that it is safe to simply
	     decrease the size of prev_nop_frag.  */
	  frag_wane (frag_now);
	  frag_new (0);
	  mips_move_labels ();
	}
      mips16_mark_labels ();
      mips_clear_insn_labels ();
    }
  mips_opts.noreorder++;
  mips_any_noreorder = 1;
}