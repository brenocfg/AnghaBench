#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct loops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  determine_invariantness () ; 
 int /*<<< orphan*/  determine_lsm (struct loops*) ; 
 int /*<<< orphan*/  move_computations () ; 
 int /*<<< orphan*/  tree_ssa_lim_finalize () ; 
 int /*<<< orphan*/  tree_ssa_lim_initialize (struct loops*) ; 

void
tree_ssa_lim (struct loops *loops)
{
  tree_ssa_lim_initialize (loops);

  /* For each statement determine the outermost loop in that it is
     invariant and cost for computing the invariant.  */
  determine_invariantness ();

  /* For each memory reference determine whether it is possible to hoist it
     out of the loop.  Force the necessary invariants to be moved out of the
     loops as well.  */
  determine_lsm (loops);

  /* Move the expressions that are expensive enough.  */
  move_computations ();

  tree_ssa_lim_finalize ();
}