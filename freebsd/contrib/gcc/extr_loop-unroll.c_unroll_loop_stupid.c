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
struct opt_info {int dummy; } ;
struct niter_desc {int simple_p; } ;
struct loops {int dummy; } ;
struct TYPE_2__ {unsigned int times; } ;
struct loop {TYPE_1__ lpt_decision; } ;
typedef  int /*<<< orphan*/  sbitmap ;

/* Variables and functions */
 int DLTHE_FLAG_UPDATE_FREQ ; 
 int DLTHE_RECORD_COPY_NUMBER ; 
 struct opt_info* analyze_insns_in_loop (struct loop*) ; 
 int /*<<< orphan*/  apply_opt_in_copies (struct opt_info*,unsigned int,int,int) ; 
 scalar_t__ dump_file ; 
 int duplicate_loop_to_header_edge (struct loop*,int /*<<< orphan*/ ,struct loops*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ flag_split_ivs_in_unroller ; 
 scalar_t__ flag_variable_expansion_in_unroller ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,unsigned int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_opt_info (struct opt_info*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 struct niter_desc* get_simple_loop_desc (struct loop*) ; 
 int /*<<< orphan*/  loop_latch_edge (struct loop*) ; 
 int num_loop_insns (struct loop*) ; 
 int /*<<< orphan*/  opt_info_start_duplication (struct opt_info*) ; 
 int /*<<< orphan*/  sbitmap_alloc (unsigned int) ; 
 int /*<<< orphan*/  sbitmap_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unroll_loop_stupid (struct loops *loops, struct loop *loop)
{
  sbitmap wont_exit;
  unsigned nunroll = loop->lpt_decision.times;
  struct niter_desc *desc = get_simple_loop_desc (loop);
  struct opt_info *opt_info = NULL;
  bool ok;
  
  if (flag_split_ivs_in_unroller
      || flag_variable_expansion_in_unroller)
    opt_info = analyze_insns_in_loop (loop);
  
  
  wont_exit = sbitmap_alloc (nunroll + 1);
  sbitmap_zero (wont_exit);
  opt_info_start_duplication (opt_info);
  
  ok = duplicate_loop_to_header_edge (loop, loop_latch_edge (loop),
				      loops, nunroll, wont_exit,
				      NULL, NULL, NULL,
				      DLTHE_FLAG_UPDATE_FREQ
				      | (opt_info
					 ? DLTHE_RECORD_COPY_NUMBER
					   : 0));
  gcc_assert (ok);
  
  if (opt_info)
    {
      apply_opt_in_copies (opt_info, nunroll, true, true);
      free_opt_info (opt_info);
    }

  free (wont_exit);

  if (desc->simple_p)
    {
      /* We indeed may get here provided that there are nontrivial assumptions
	 for a loop to be really simple.  We could update the counts, but the
	 problem is that we are unable to decide which exit will be taken
	 (not really true in case the number of iterations is constant,
	 but noone will do anything with this information, so we do not
	 worry about it).  */
      desc->simple_p = false;
    }

  if (dump_file)
    fprintf (dump_file, ";; Unrolled loop %d times, %i insns\n",
	     nunroll, num_loop_insns (loop));
}