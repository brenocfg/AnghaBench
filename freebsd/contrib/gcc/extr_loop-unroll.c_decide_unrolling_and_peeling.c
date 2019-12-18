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
struct loops {struct loop* tree_root; } ;
struct TYPE_2__ {scalar_t__ decision; } ;
struct loop {int num; TYPE_1__ lpt_decision; int /*<<< orphan*/  av_ninsns; int /*<<< orphan*/  ninsns; struct loop* inner; int /*<<< orphan*/  header; struct loop* outer; struct loop* next; } ;

/* Variables and functions */
 scalar_t__ LPT_NONE ; 
 int /*<<< orphan*/  average_num_loop_insns (struct loop*) ; 
 int /*<<< orphan*/  can_duplicate_loop_p (struct loop*) ; 
 int /*<<< orphan*/  decide_peel_simple (struct loop*,int) ; 
 int /*<<< orphan*/  decide_unroll_constant_iterations (struct loop*,int) ; 
 int /*<<< orphan*/  decide_unroll_runtime_iterations (struct loop*,int) ; 
 int /*<<< orphan*/  decide_unroll_stupid (struct loop*,int) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  maybe_hot_bb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_loop_insns (struct loop*) ; 

__attribute__((used)) static void
decide_unrolling_and_peeling (struct loops *loops, int flags)
{
  struct loop *loop = loops->tree_root, *next;

  while (loop->inner)
    loop = loop->inner;

  /* Scan the loops, inner ones first.  */
  while (loop != loops->tree_root)
    {
      if (loop->next)
	{
	  next = loop->next;
	  while (next->inner)
	    next = next->inner;
	}
      else
	next = loop->outer;

      loop->lpt_decision.decision = LPT_NONE;

      if (dump_file)
	fprintf (dump_file, "\n;; *** Considering loop %d ***\n", loop->num);

      /* Do not peel cold areas.  */
      if (!maybe_hot_bb_p (loop->header))
	{
	  if (dump_file)
	    fprintf (dump_file, ";; Not considering loop, cold area\n");
	  loop = next;
	  continue;
	}

      /* Can the loop be manipulated?  */
      if (!can_duplicate_loop_p (loop))
	{
	  if (dump_file)
	    fprintf (dump_file,
		     ";; Not considering loop, cannot duplicate\n");
	  loop = next;
	  continue;
	}

      /* Skip non-innermost loops.  */
      if (loop->inner)
	{
	  if (dump_file)
	    fprintf (dump_file, ";; Not considering loop, is not innermost\n");
	  loop = next;
	  continue;
	}

      loop->ninsns = num_loop_insns (loop);
      loop->av_ninsns = average_num_loop_insns (loop);

      /* Try transformations one by one in decreasing order of
	 priority.  */

      decide_unroll_constant_iterations (loop, flags);
      if (loop->lpt_decision.decision == LPT_NONE)
	decide_unroll_runtime_iterations (loop, flags);
      if (loop->lpt_decision.decision == LPT_NONE)
	decide_unroll_stupid (loop, flags);
      if (loop->lpt_decision.decision == LPT_NONE)
	decide_peel_simple (loop, flags);

      loop = next;
    }
}