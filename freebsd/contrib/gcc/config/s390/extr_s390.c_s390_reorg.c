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
struct constant_pool {int dummy; } ;
typedef  scalar_t__ rtx ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {int decomposed_literal_pool_addresses_ok_p; int split_branches_pending_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_ADDRESSES_NEW (scalar_t__,int) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ TARGET_CPU_ZARCH ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* cfun ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ emit_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  s390_chunkify_cancel (struct constant_pool*) ; 
 int /*<<< orphan*/  s390_chunkify_finish (struct constant_pool*) ; 
 struct constant_pool* s390_chunkify_start () ; 
 scalar_t__ s390_execute_label (scalar_t__) ; 
 int /*<<< orphan*/  s390_execute_target (scalar_t__) ; 
 int /*<<< orphan*/  s390_mainpool_cancel (struct constant_pool*) ; 
 int /*<<< orphan*/  s390_mainpool_finish (struct constant_pool*) ; 
 struct constant_pool* s390_mainpool_start () ; 
 int /*<<< orphan*/  s390_optimize_prologue () ; 
 scalar_t__ s390_split_branches () ; 
 int /*<<< orphan*/  split_all_insns_noflow () ; 

__attribute__((used)) static void
s390_reorg (void)
{
  bool pool_overflow = false;

  /* Make sure all splits have been performed; splits after
     machine_dependent_reorg might confuse insn length counts.  */
  split_all_insns_noflow ();

  /* From here on decomposed literal pool addresses must be accepted.  */
  cfun->machine->decomposed_literal_pool_addresses_ok_p = true;

  /* Install the main literal pool and the associated base
     register load insns.

     In addition, there are two problematic situations we need
     to correct:

     - the literal pool might be > 4096 bytes in size, so that
       some of its elements cannot be directly accessed

     - a branch target might be > 64K away from the branch, so that
       it is not possible to use a PC-relative instruction.

     To fix those, we split the single literal pool into multiple
     pool chunks, reloading the pool base register at various
     points throughout the function to ensure it always points to
     the pool chunk the following code expects, and / or replace
     PC-relative branches by absolute branches.

     However, the two problems are interdependent: splitting the
     literal pool can move a branch further away from its target,
     causing the 64K limit to overflow, and on the other hand,
     replacing a PC-relative branch by an absolute branch means
     we need to put the branch target address into the literal
     pool, possibly causing it to overflow.

     So, we loop trying to fix up both problems until we manage
     to satisfy both conditions at the same time.  Note that the
     loop is guaranteed to terminate as every pass of the loop
     strictly decreases the total number of PC-relative branches
     in the function.  (This is not completely true as there
     might be branch-over-pool insns introduced by chunkify_start.
     Those never need to be split however.)  */

  for (;;)
    {
      struct constant_pool *pool = NULL;

      /* Collect the literal pool.  */
      if (!pool_overflow)
	{
	  pool = s390_mainpool_start ();
	  if (!pool)
	    pool_overflow = true;
	}

      /* If literal pool overflowed, start to chunkify it.  */
      if (pool_overflow)
        pool = s390_chunkify_start ();

      /* Split out-of-range branches.  If this has created new
	 literal pool entries, cancel current chunk list and
	 recompute it.  zSeries machines have large branch
	 instructions, so we never need to split a branch.  */
      if (!TARGET_CPU_ZARCH && s390_split_branches ())
        {
          if (pool_overflow)
            s390_chunkify_cancel (pool);
	  else
            s390_mainpool_cancel (pool);

          continue;
        }

      /* If we made it up to here, both conditions are satisfied.
	 Finish up literal pool related changes.  */
      if (pool_overflow)
	s390_chunkify_finish (pool);
      else
	s390_mainpool_finish (pool);

      /* We're done splitting branches.  */
      cfun->machine->split_branches_pending_p = false;
      break;
    }

  /* Generate out-of-pool execute target insns.  */
  if (TARGET_CPU_ZARCH)
    {
      rtx insn, label, target;

      for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
	{
	  label = s390_execute_label (insn);
	  if (!label)
	    continue;

	  gcc_assert (label != const0_rtx);

	  target = emit_label (XEXP (label, 0));
	  INSN_ADDRESSES_NEW (target, -1);

	  target = emit_insn (s390_execute_target (insn));
	  INSN_ADDRESSES_NEW (target, -1);
	}
    }

  /* Try to optimize prologue and epilogue further.  */
  s390_optimize_prologue ();
}