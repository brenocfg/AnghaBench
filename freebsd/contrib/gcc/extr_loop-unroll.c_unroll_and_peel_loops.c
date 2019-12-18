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
struct TYPE_2__ {int decision; } ;
struct loop {TYPE_1__ lpt_decision; struct loop* outer; struct loop* inner; struct loop* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
#define  LPT_NONE 133 
#define  LPT_PEEL_COMPLETELY 132 
#define  LPT_PEEL_SIMPLE 131 
#define  LPT_UNROLL_CONSTANT 130 
#define  LPT_UNROLL_RUNTIME 129 
#define  LPT_UNROLL_STUPID 128 
 int /*<<< orphan*/  decide_unrolling_and_peeling (struct loops*,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  iv_analysis_done () ; 
 int /*<<< orphan*/  peel_loop_simple (struct loops*,struct loop*) ; 
 int /*<<< orphan*/  peel_loops_completely (struct loops*,int) ; 
 int /*<<< orphan*/  unroll_loop_constant_iterations (struct loops*,struct loop*) ; 
 int /*<<< orphan*/  unroll_loop_runtime_iterations (struct loops*,struct loop*) ; 
 int /*<<< orphan*/  unroll_loop_stupid (struct loops*,struct loop*) ; 
 int /*<<< orphan*/  verify_dominators (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_loop_structure (struct loops*) ; 

void
unroll_and_peel_loops (struct loops *loops, int flags)
{
  struct loop *loop, *next;
  bool check;

  /* First perform complete loop peeling (it is almost surely a win,
     and affects parameters for further decision a lot).  */
  peel_loops_completely (loops, flags);

  /* Now decide rest of unrolling and peeling.  */
  decide_unrolling_and_peeling (loops, flags);

  loop = loops->tree_root;
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

      check = true;
      /* And perform the appropriate transformations.  */
      switch (loop->lpt_decision.decision)
	{
	case LPT_PEEL_COMPLETELY:
	  /* Already done.  */
	  gcc_unreachable ();
	case LPT_PEEL_SIMPLE:
	  peel_loop_simple (loops, loop);
	  break;
	case LPT_UNROLL_CONSTANT:
	  unroll_loop_constant_iterations (loops, loop);
	  break;
	case LPT_UNROLL_RUNTIME:
	  unroll_loop_runtime_iterations (loops, loop);
	  break;
	case LPT_UNROLL_STUPID:
	  unroll_loop_stupid (loops, loop);
	  break;
	case LPT_NONE:
	  check = false;
	  break;
	default:
	  gcc_unreachable ();
	}
      if (check)
	{
#ifdef ENABLE_CHECKING
	  verify_dominators (CDI_DOMINATORS);
	  verify_loop_structure (loops);
#endif
	}
      loop = next;
    }

  iv_analysis_done ();
}