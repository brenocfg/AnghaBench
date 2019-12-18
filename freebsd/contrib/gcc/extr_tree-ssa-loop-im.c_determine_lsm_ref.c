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
struct mem_ref_loc {int /*<<< orphan*/  stmt; struct mem_ref_loc* next; } ;
struct mem_ref {struct mem_ref_loc* locs; int /*<<< orphan*/  mem; int /*<<< orphan*/  vops; int /*<<< orphan*/  is_stored; } ;
struct loop {int dummy; } ;
typedef  int /*<<< orphan*/  edge ;
typedef  int /*<<< orphan*/  bitmap ;
struct TYPE_2__ {struct loop* always_executed_in; } ;

/* Variables and functions */
 TYPE_1__* LIM_DATA (int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_intersect_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flow_loop_nested_p (struct loop*,struct loop*) ; 
 int /*<<< orphan*/  schedule_sm (struct loop*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,struct mem_ref_loc*) ; 
 scalar_t__ tree_could_trap_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
determine_lsm_ref (struct loop *loop, edge *exits, unsigned n_exits,
		   bitmap clobbered_vops, struct mem_ref *ref)
{
  struct mem_ref_loc *aref;
  struct loop *must_exec;

  /* In case the memory is not stored to, there is nothing for SM to do.  */
  if (!ref->is_stored)
    return;

  /* If the reference is aliased with any different ref, or killed by call
     in function, then fail.  */
  if (bitmap_intersect_p (ref->vops, clobbered_vops))
    return;

  if (tree_could_trap_p (ref->mem))
    {
      /* If the memory access is unsafe (i.e. it might trap), ensure that some
	 of the statements in that it occurs is always executed when the loop
	 is entered.  This way we know that by moving the load from the
	 reference out of the loop we will not cause the error that would not
	 occur otherwise.

	 TODO -- in fact we would like to check for anticipability of the
	 reference, i.e. that on each path from loop entry to loop exit at
	 least one of the statements containing the memory reference is
	 executed.  */

      for (aref = ref->locs; aref; aref = aref->next)
	{
	  if (!LIM_DATA (aref->stmt))
	    continue;

	  must_exec = LIM_DATA (aref->stmt)->always_executed_in;
	  if (!must_exec)
	    continue;

	  if (must_exec == loop
	      || flow_loop_nested_p (must_exec, loop))
	    break;
	}

      if (!aref)
	return;
    }

  schedule_sm (loop, exits, n_exits, ref->mem, ref->locs);
}