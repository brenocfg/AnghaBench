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
struct niter_desc {int niter; scalar_t__ noloop_assumptions; scalar_t__ assumptions; int /*<<< orphan*/  const_iter; int /*<<< orphan*/  simple_p; } ;
struct TYPE_2__ {unsigned int times; int /*<<< orphan*/  decision; } ;
struct loop {unsigned int ninsns; unsigned int av_ninsns; TYPE_1__ lpt_decision; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPT_UNROLL_CONSTANT ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PARAM_MAX_AVERAGE_UNROLLED_INSNS ; 
 int /*<<< orphan*/  PARAM_MAX_UNROLLED_INSNS ; 
 int /*<<< orphan*/  PARAM_MAX_UNROLL_TIMES ; 
 unsigned int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 int UAP_UNROLL ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 struct niter_desc* get_simple_loop_desc (struct loop*) ; 
 int /*<<< orphan*/  loop_exit_at_end_p (struct loop*) ; 

__attribute__((used)) static void
decide_unroll_constant_iterations (struct loop *loop, int flags)
{
  unsigned nunroll, nunroll_by_av, best_copies, best_unroll = 0, n_copies, i;
  struct niter_desc *desc;

  if (!(flags & UAP_UNROLL))
    {
      /* We were not asked to, just return back silently.  */
      return;
    }

  if (dump_file)
    fprintf (dump_file,
	     "\n;; Considering unrolling loop with constant "
	     "number of iterations\n");

  /* nunroll = total number of copies of the original loop body in
     unrolled loop (i.e. if it is 2, we have to duplicate loop body once.  */
  nunroll = PARAM_VALUE (PARAM_MAX_UNROLLED_INSNS) / loop->ninsns;
  nunroll_by_av
    = PARAM_VALUE (PARAM_MAX_AVERAGE_UNROLLED_INSNS) / loop->av_ninsns;
  if (nunroll > nunroll_by_av)
    nunroll = nunroll_by_av;
  if (nunroll > (unsigned) PARAM_VALUE (PARAM_MAX_UNROLL_TIMES))
    nunroll = PARAM_VALUE (PARAM_MAX_UNROLL_TIMES);

  /* Skip big loops.  */
  if (nunroll <= 1)
    {
      if (dump_file)
	fprintf (dump_file, ";; Not considering loop, is too big\n");
      return;
    }

  /* Check for simple loops.  */
  desc = get_simple_loop_desc (loop);

  /* Check number of iterations.  */
  if (!desc->simple_p || !desc->const_iter || desc->assumptions)
    {
      if (dump_file)
	fprintf (dump_file,
		 ";; Unable to prove that the loop iterates constant times\n");
      return;
    }

  /* Check whether the loop rolls enough to consider.  */
  if (desc->niter < 2 * nunroll)
    {
      if (dump_file)
	fprintf (dump_file, ";; Not unrolling loop, doesn't roll\n");
      return;
    }

  /* Success; now compute number of iterations to unroll.  We alter
     nunroll so that as few as possible copies of loop body are
     necessary, while still not decreasing the number of unrollings
     too much (at most by 1).  */
  best_copies = 2 * nunroll + 10;

  i = 2 * nunroll + 2;
  if (i - 1 >= desc->niter)
    i = desc->niter - 2;

  for (; i >= nunroll - 1; i--)
    {
      unsigned exit_mod = desc->niter % (i + 1);

      if (!loop_exit_at_end_p (loop))
	n_copies = exit_mod + i + 1;
      else if (exit_mod != (unsigned) i
	       || desc->noloop_assumptions != NULL_RTX)
	n_copies = exit_mod + i + 2;
      else
	n_copies = i + 1;

      if (n_copies < best_copies)
	{
	  best_copies = n_copies;
	  best_unroll = i;
	}
    }

  if (dump_file)
    fprintf (dump_file, ";; max_unroll %d (%d copies, initial %d).\n",
	     best_unroll + 1, best_copies, nunroll);

  loop->lpt_decision.decision = LPT_UNROLL_CONSTANT;
  loop->lpt_decision.times = best_unroll;
  
  if (dump_file)
    fprintf (dump_file,
	     ";; Decided to unroll the constant times rolling loop, %d times.\n",
	     loop->lpt_decision.times);
}