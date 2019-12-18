#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct niter_desc {scalar_t__ const_iter; scalar_t__ assumptions; int /*<<< orphan*/  simple_p; } ;
struct TYPE_4__ {unsigned int times; int /*<<< orphan*/  decision; } ;
struct loop {unsigned int ninsns; unsigned int av_ninsns; TYPE_2__ lpt_decision; TYPE_1__* header; } ;
struct TYPE_3__ {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPT_UNROLL_RUNTIME ; 
 int /*<<< orphan*/  PARAM_MAX_AVERAGE_UNROLLED_INSNS ; 
 int /*<<< orphan*/  PARAM_MAX_UNROLLED_INSNS ; 
 int /*<<< orphan*/  PARAM_MAX_UNROLL_TIMES ; 
 unsigned int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 int UAP_UNROLL ; 
 scalar_t__ dump_file ; 
 int expected_loop_iterations (struct loop*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 struct niter_desc* get_simple_loop_desc (struct loop*) ; 

__attribute__((used)) static void
decide_unroll_runtime_iterations (struct loop *loop, int flags)
{
  unsigned nunroll, nunroll_by_av, i;
  struct niter_desc *desc;

  if (!(flags & UAP_UNROLL))
    {
      /* We were not asked to, just return back silently.  */
      return;
    }

  if (dump_file)
    fprintf (dump_file,
	     "\n;; Considering unrolling loop with runtime "
	     "computable number of iterations\n");

  /* nunroll = total number of copies of the original loop body in
     unrolled loop (i.e. if it is 2, we have to duplicate loop body once.  */
  nunroll = PARAM_VALUE (PARAM_MAX_UNROLLED_INSNS) / loop->ninsns;
  nunroll_by_av = PARAM_VALUE (PARAM_MAX_AVERAGE_UNROLLED_INSNS) / loop->av_ninsns;
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

  /* Check simpleness.  */
  if (!desc->simple_p || desc->assumptions)
    {
      if (dump_file)
	fprintf (dump_file,
		 ";; Unable to prove that the number of iterations "
		 "can be counted in runtime\n");
      return;
    }

  if (desc->const_iter)
    {
      if (dump_file)
	fprintf (dump_file, ";; Loop iterates constant times\n");
      return;
    }

  /* If we have profile feedback, check whether the loop rolls.  */
  if (loop->header->count && expected_loop_iterations (loop) < 2 * nunroll)
    {
      if (dump_file)
	fprintf (dump_file, ";; Not unrolling loop, doesn't roll\n");
      return;
    }

  /* Success; now force nunroll to be power of 2, as we are unable to
     cope with overflows in computation of number of iterations.  */
  for (i = 1; 2 * i <= nunroll; i *= 2)
    continue;

  loop->lpt_decision.decision = LPT_UNROLL_RUNTIME;
  loop->lpt_decision.times = i - 1;
  
  if (dump_file)
    fprintf (dump_file,
	     ";; Decided to unroll the runtime computable "
	     "times rolling loop, %d times.\n",
	     loop->lpt_decision.times);
}