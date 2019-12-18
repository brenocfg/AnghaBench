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
struct niter_desc {int /*<<< orphan*/  assumptions; scalar_t__ simple_p; } ;
struct TYPE_4__ {unsigned int times; int /*<<< orphan*/  decision; } ;
struct loop {unsigned int ninsns; unsigned int av_ninsns; TYPE_2__ lpt_decision; TYPE_1__* header; } ;
struct TYPE_3__ {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPT_UNROLL_STUPID ; 
 int /*<<< orphan*/  PARAM_MAX_AVERAGE_UNROLLED_INSNS ; 
 int /*<<< orphan*/  PARAM_MAX_UNROLLED_INSNS ; 
 int /*<<< orphan*/  PARAM_MAX_UNROLL_TIMES ; 
 unsigned int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 int UAP_UNROLL_ALL ; 
 scalar_t__ dump_file ; 
 int expected_loop_iterations (struct loop*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 struct niter_desc* get_simple_loop_desc (struct loop*) ; 
 int num_loop_branches (struct loop*) ; 

__attribute__((used)) static void
decide_unroll_stupid (struct loop *loop, int flags)
{
  unsigned nunroll, nunroll_by_av, i;
  struct niter_desc *desc;

  if (!(flags & UAP_UNROLL_ALL))
    {
      /* We were not asked to, just return back silently.  */
      return;
    }

  if (dump_file)
    fprintf (dump_file, "\n;; Considering unrolling loop stupidly\n");

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

  /* Check simpleness.  */
  if (desc->simple_p && !desc->assumptions)
    {
      if (dump_file)
	fprintf (dump_file, ";; The loop is simple\n");
      return;
    }

  /* Do not unroll loops with branches inside -- it increases number
     of mispredicts.  */
  if (num_loop_branches (loop) > 1)
    {
      if (dump_file)
	fprintf (dump_file, ";; Not unrolling, contains branches\n");
      return;
    }

  /* If we have profile feedback, check whether the loop rolls.  */
  if (loop->header->count
      && expected_loop_iterations (loop) < 2 * nunroll)
    {
      if (dump_file)
	fprintf (dump_file, ";; Not unrolling loop, doesn't roll\n");
      return;
    }

  /* Success.  Now force nunroll to be power of 2, as it seems that this
     improves results (partially because of better alignments, partially
     because of some dark magic).  */
  for (i = 1; 2 * i <= nunroll; i *= 2)
    continue;

  loop->lpt_decision.decision = LPT_UNROLL_STUPID;
  loop->lpt_decision.times = i - 1;
      
  if (dump_file)
    fprintf (dump_file,
	     ";; Decided to unroll the loop stupidly, %d times.\n",
	     loop->lpt_decision.times);
}